#include "csiebox_client.h"

#include "csiebox_common.h"
#include "connect.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h> //for select()
#include <sys/types.h>
#include <dirent.h>
#include <utime.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <linux/inotify.h> //for inotify()

static int parse_arg(csiebox_client* client, int argc, char** argv);
static int login(csiebox_client* client);
static int prepare_and_sync(csiebox_client* client);
static void sync_all(csiebox_client* client, char* longest_path, int level);

static char* check_walked_dir(csiebox_client* client);
static void sync_file(csiebox_client* client, char* path);
static csiebox_protocol_status sync_file_meta(csiebox_client* client, char* path);
static void sync_file_data(csiebox_client* client, char* path);
static char* convert_to_relative_path(csiebox_client* client, const char* path);
static void monitor_home(csiebox_client* client);
static void rm_file(csiebox_client* client, char* path, int is_dir);
static void add_inotify(csiebox_client* client, char* path);
static void handle_inotify(csiebox_client* client);

/* reverse sync */
static void reverse_sync(csiebox_client* client);
static int reverse_handle_request(csiebox_client* client, csiebox_protocol_header* header);
static void reverse_sync_file(csiebox_client* client, csiebox_protocol_meta* meta);
/* reverse sync end */


#define IN_FLAG (IN_CREATE | IN_DELETE | IN_ATTRIB | IN_MODIFY)
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))
#define DIR_MAX 1000

int max_level = 0;

//read config file, and connect to server
void csiebox_client_init(
  csiebox_client** client, int argc, char** argv) {
  csiebox_client* tmp = (csiebox_client*)malloc(sizeof(csiebox_client));
  if (!tmp) {
    fprintf(stderr, "client malloc fail\n");
    return;
  }
  memset(tmp, 0, sizeof(csiebox_client));
  if (!parse_arg(tmp, argc, argv)) {
    fprintf(stderr, "Usage: %s [config file]\n", argv[0]);
    free(tmp);
    return;
  }
  int fd = client_start(tmp->arg.name, tmp->arg.server);
  if (fd < 0) {
    fprintf(stderr, "connect fail\n");
    free(tmp);
    return;
  }
  tmp->conn_fd = fd;
  fd = inotify_init();
  if (fd < 0) {
    fprintf(stderr, "inotify fail\n");
    close(tmp->conn_fd);
    free(tmp);
    return;
  }
  tmp->inotify_fd = fd;
  if (!init_hash(&(tmp->inotify_hash), 100)) {
    destroy_hash(&(tmp->inotify_hash));
    fprintf(stderr, "hash fail\n");
    close(tmp->conn_fd);
    close(tmp->inotify_fd);
    free(tmp);
  }
  memset(tmp->root, 0, PATH_MAX);
  realpath(tmp->arg.path, tmp->root);
  *client = tmp;
}

//this is where client sends request, you sould write your code here
int csiebox_client_run(csiebox_client* client) {
  if (!login(client)) {
    fprintf(stderr, "login fail\n");
    return 0;
  }
  fprintf(stderr, "login success\n");
  
  if (!prepare_and_sync(client)) {
    fprintf(stderr, "sync fail\n");
    return 0;
  }
  
  reverse_sync(client);
  fprintf(stderr, "reverse sync success\n");

  fprintf(stderr, "monitor start\n");
  monitor_home(client);
  fprintf(stderr, "monitor end\n");
  return 1;
}

void csiebox_client_destroy(csiebox_client** client) {
  csiebox_client* tmp = *client;
  *client = 0;
  if (!tmp) {
    return;
  }
  close(tmp->conn_fd);
  free(tmp);
}

//read config file
static int parse_arg(csiebox_client* client, int argc, char** argv) {
  if (argc != 2) {
    return 0;
  }
  FILE* file = fopen(argv[1], "r");
  if (!file) {
    return 0;
  }
  fprintf(stderr, "reading config...\n");
  size_t keysize = 20, valsize = 20;
  char* key = (char*)malloc(sizeof(char) * keysize);
  char* val = (char*)malloc(sizeof(char) * valsize);
  ssize_t keylen, vallen;
  int accept_config_total = 5;
  int accept_config[5] = {0, 0, 0, 0, 0};
  while ((keylen = getdelim(&key, &keysize, '=', file) - 1) > 0) {
    key[keylen] = '\0';
    vallen = getline(&val, &valsize, file) - 1;
    val[vallen] = '\0';
    fprintf(stderr, "config (%d, %s)=(%d, %s)\n", keylen, key, vallen, val);
    if (strcmp("name", key) == 0) {
      if (vallen <= sizeof(client->arg.name)) {
        strncpy(client->arg.name, val, vallen);
        accept_config[0] = 1;
      }
    } else if (strcmp("server", key) == 0) {
      if (vallen <= sizeof(client->arg.server)) {
        strncpy(client->arg.server, val, vallen);
        accept_config[1] = 1;
      }
    } else if (strcmp("user", key) == 0) {
      if (vallen <= sizeof(client->arg.user)) {
        strncpy(client->arg.user, val, vallen);
        accept_config[2] = 1;
      }
    } else if (strcmp("passwd", key) == 0) {
      if (vallen <= sizeof(client->arg.passwd)) {
        strncpy(client->arg.passwd, val, vallen);
        accept_config[3] = 1;
      }
    } else if (strcmp("path", key) == 0) {
      if (vallen <= sizeof(client->arg.path)) {
        strncpy(client->arg.path, val, vallen);
        accept_config[4] = 1;
      }
    }
  }
  free(key);
  free(val);
  fclose(file);
  int i, test = 1;
  for (i = 0; i < accept_config_total; ++i) {
    test = test & accept_config[i];
  }
  if (!test) {
    fprintf(stderr, "config error\n");
    return 0;
  }
  return 1;
}

static int login(csiebox_client* client) {
  csiebox_protocol_login req;
  memset(&req, 0, sizeof(req));
  req.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  req.message.header.req.op = CSIEBOX_PROTOCOL_OP_LOGIN;
  req.message.header.req.datalen = sizeof(req) - sizeof(req.message.header);
  memcpy(req.message.body.user, client->arg.user, strlen(client->arg.user));
  md5(client->arg.passwd,
      strlen(client->arg.passwd),
      req.message.body.passwd_hash);
  if (!send_message(client->conn_fd, &req, sizeof(req))) {
    fprintf(stderr, "send fail\n");
    return 0;
  }
  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  if (recv_message(client->conn_fd, &header, sizeof(header))) {
    if (header.res.magic == CSIEBOX_PROTOCOL_MAGIC_RES &&
        header.res.op == CSIEBOX_PROTOCOL_OP_LOGIN &&
        header.res.status == CSIEBOX_PROTOCOL_STATUS_OK) {
      client->client_id = header.res.client_id;
      return 1;
    } else {
      return 0;
    }
  }
  return 0;
}


static int prepare_and_sync(csiebox_client* client) {
  char* cwd = (char*)malloc(sizeof(char) * PATH_MAX);
  memset(cwd, 0, sizeof(cwd));
  if (getcwd(cwd, PATH_MAX) == 0) {
    fprintf(stderr, "getcwd fail\n");
    fprintf(stderr, "code: %s\n", strerror(errno));
    free(cwd);
    return 0;
  }
  if (chdir(client->arg.path) != 0) {
    fprintf(stderr, "invalid client path\n");
    free(cwd);
    return 0;
  }
  max_level = 0;
  char* longest_path = (char*)malloc(sizeof(char) * PATH_MAX);
  sync_all(client, longest_path, 0);
  
  FILE *fp = fopen("longestPath.txt", "w+");
  int i = 0, len = strlen(longest_path);
  for (; i<len-1; i++) {
    longest_path[i] = longest_path[i+1]; 
  }
  longest_path[len-1] = 0;
  fwrite(longest_path, 1, strlen(longest_path), fp);
  fclose(fp);
  free(longest_path);
  
  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_END;
  header.req.client_id = client->client_id;
  send_message(client->conn_fd, &header, sizeof(header));
  chdir(cwd);
  free(cwd);
  return 1;
}

static void sync_all(csiebox_client* client, char* longest_path, int level) {
  char* cwd = (char*)malloc(sizeof(char) * PATH_MAX);
  memset(cwd, 0, sizeof(char) * PATH_MAX);
  if (getcwd(cwd, PATH_MAX) == 0) {
    fprintf(stderr, "getcwd fail\n");
  }
  add_inotify(client, cwd); /* add wd */
  DIR* dir;
  struct dirent* file;
  struct stat file_stat;
  dir = opendir(".");
  while ((file = readdir(dir)) != NULL) {
    if (strcmp(file->d_name, ".") == 0 ||
        strcmp(file->d_name, "..") == 0) {
    continue;
    }
    lstat(file->d_name, &file_stat); 
    sync_file(client, file->d_name);
    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      level++;
      if (level > max_level){
        max_level = level;
        strcpy(longest_path, convert_to_relative_path(client, file->d_name));
      }
      if (chdir(file->d_name) != 0) {
        fprintf(stderr, "bad dir %s\n", file->d_name);
        continue;
      }
      sync_all(client, longest_path, level); /* go to next level */
      chdir(cwd);
    }
  }
  closedir(dir);
  free(cwd);
  return;
}

static void sync_file(csiebox_client* client, char* path) {
  csiebox_protocol_status status;
  status = sync_file_meta(client, path);
  if (status == CSIEBOX_PROTOCOL_STATUS_MORE) {
    sync_file_data(client, path);
  }
}

static csiebox_protocol_status sync_file_meta(csiebox_client* client, char* path) {
  char* relative = convert_to_relative_path(client, path);
  if (!relative) {
    fprintf(stderr, "convert relative fail: %s\n", path);
    return CSIEBOX_PROTOCOL_STATUS_FAIL;
  }
  csiebox_protocol_meta meta;
  memset(&meta, 0, sizeof(meta));
  meta.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  meta.message.header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_META;
  meta.message.header.req.client_id = client->client_id;
  meta.message.header.req.datalen = sizeof(meta) - sizeof(csiebox_protocol_header);
  meta.message.body.pathlen = strlen(relative);
  lstat(path, &(meta.message.body.stat));
  if ((meta.message.body.stat.st_mode & S_IFMT) == S_IFDIR) { /* dir: do nothing */
  } else {
    md5_file(path, meta.message.body.hash); /* file: send a hash */
  }
  send_message(client->conn_fd, &meta, sizeof(meta));
  send_message(client->conn_fd, relative, strlen(relative));
  free(relative);
  

  csiebox_protocol_header header;
  recv_message(client->conn_fd, &header, sizeof(header));
  if (header.res.status == CSIEBOX_PROTOCOL_STATUS_FAIL) {
    fprintf(stderr, "sync meta fail: %s\n", path);
    return;
  }
  return header.res.status;
}

static void sync_file_data(
  csiebox_client* client, char* path) {
  fprintf(stderr, "file_data: %s\n", path);
  struct stat stat;
  memset(&stat, 0, sizeof(stat));
  lstat(path, &stat);
  csiebox_protocol_file file;
  memset(&file, 0, sizeof(file));
  file.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  file.message.header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_FILE;
  file.message.header.req.client_id = client->client_id;
  file.message.header.req.datalen = sizeof(file) - sizeof(csiebox_protocol_header);
  if ((stat.st_mode & S_IFMT) == S_IFDIR) {
    file.message.body.datalen = 0;
    fprintf(stderr, "dir datalen: %zu\n", file.message.body.datalen);
    send_message(client->conn_fd, &file, sizeof(file));
  } else {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
      fprintf(stderr, "open fail\n");
      file.message.body.datalen = 0;
      send_message(client->conn_fd, &file, sizeof(file));
    } else {
      file.message.body.datalen = lseek(fd, 0, SEEK_END);
      fprintf(stderr, "else datalen: %zd\n", file.message.body.datalen);
      send_message(client->conn_fd, &file, sizeof(file));
      lseek(fd, 0, SEEK_SET);
      char buf[4096];
      memset(buf, 0, 4096);
      size_t readlen;
      while ((readlen = read(fd, buf, 4096)) > 0) {
        send_message(client->conn_fd, buf, readlen);
      }
      close(fd);
    }
  }

  csiebox_protocol_header header;
  recv_message(client->conn_fd, &header, sizeof(header));
  if (header.res.status != CSIEBOX_PROTOCOL_STATUS_OK) {
    fprintf(stderr, "sync data fail: %s\n", path);
  }
}

static char* convert_to_relative_path(csiebox_client* client, const char* path) {
  char* ret = (char*)malloc(sizeof(char) * PATH_MAX);
  if (path[0] == '/') {
    strcpy(ret, path);
  } else {
    char dir[PATH_MAX];
    memset(dir, 0, PATH_MAX);
    getcwd(dir, PATH_MAX);
    sprintf(ret, "%s/%s", dir, path);
  }
  if (strncmp(client->root, ret, strlen(client->root)) != 0) {
    free(ret);
    return NULL;
  }
  size_t rootlen = strlen(client->root);
  size_t retlen = strlen(ret);
  size_t i;
  for (i = 0; i < retlen; ++i) {
    if (i < rootlen) {
      ret[i] = ret[i + rootlen];
    } else {
      ret[i] = 0;
    }
  }
  return ret;
}

static void monitor_home(csiebox_client* client) {
  while (1) {
    handle_inotify(client);
  }
}

static void rm_file(csiebox_client* client, char* path, int is_dir) {
  char* relative = convert_to_relative_path(client, path);
  if (!relative) {
    fprintf(stderr, "conver relative fail\n");
    return;
  }
  if (is_dir) {
    int wd = get_from_hash_by_path(&(client->inotify_hash), (void*)path, 0);
    inotify_rm_watch(client->inotify_fd, wd);
    char* tmp = NULL;
    del_from_hash(&(client->inotify_hash), (void**)&tmp, wd); /* remove inotify */
    free(tmp);
  }
  csiebox_protocol_rm rm;
  memset(&rm, 0, sizeof(rm));
  rm.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  rm.message.header.req.op = CSIEBOX_PROTOCOL_OP_RM;
  rm.message.header.req.client_id = client->client_id;
  rm.message.header.req.datalen = sizeof(rm) - sizeof(csiebox_protocol_header);
  rm.message.body.pathlen = strlen(relative);
  send_message(client->conn_fd, &rm, sizeof(rm));
  send_message(client->conn_fd, relative, strlen(relative));
  csiebox_protocol_header header;
  recv_message(client->conn_fd, &header, sizeof(header));
  if (header.res.status != CSIEBOX_PROTOCOL_STATUS_OK) {
    fprintf(stderr, "rm fail: %s\n", path);
  }
  free(relative);
}

static void add_inotify(csiebox_client* client, char* path) {
  int wd = inotify_add_watch(client->inotify_fd, path, IN_FLAG);
  char* inotify_path = (char*)malloc(sizeof(char) * strlen(path)+1);
  memset(inotify_path, 0, strlen(path));
  memcpy(inotify_path, path, strlen(path));
  put_into_hash(&(client->inotify_hash), (void*)inotify_path, wd);
}

static void handle_inotify(csiebox_client* client) {
  int len = 0, i = 0;
  char buffer[EVENT_BUF_LEN];
  memset(buffer, 0, EVENT_BUF_LEN);
 
  if ((len = read(client->inotify_fd, buffer, EVENT_BUF_LEN)) <= 0) {
    return;
  }
  
  i = 0;
  while (i < len) {
    struct inotify_event* event = (struct inotify_event*)&buffer[i];
    char path[PATH_MAX];
    memset(path, 0, PATH_MAX);
    char* wd_path;
    if (!get_from_hash(&(client->inotify_hash), (void**)&wd_path, event->wd)) {
      continue;
    }
    sprintf(path, "%s/", wd_path);
    strncat(path, event->name, event->len);
    fprintf(stderr, "wd: %d\n", event->wd);
    if (event->mask & IN_CREATE) {
      fprintf(stderr, "type: create\n");
      fprintf(stderr, "sync file: %s\n", path);
      sync_file(client, path); /* create file */
      if (event->mask & IN_ISDIR) {
        add_inotify(client, path); /* if create dir, have to inotify, too */
      }
    } else if (event->mask & IN_ATTRIB){
      fprintf(stderr, "type: attrib\n");
      fprintf(stderr, "sync file meta: %s\n", path);
      sync_file_meta(client, path); /* change mode or time or create dir, and return status */
    } else if (event->mask & IN_DELETE) {
      fprintf(stderr, "type: delete\n");
      fprintf(stderr, "rm file: %s\n", path);
      rm_file(client, path, event->mask & IN_ISDIR);
    } else {
      fprintf(stderr, "type: modify\n");
      fprintf(stderr, "sync file: %s\n", path);
      sync_file(client, path); /* re-create file */
    }
    i += EVENT_SIZE + event->len;
  }
  memset(buffer, 0, EVENT_BUF_LEN);
}

/* reverse sync */
static void reverse_sync(csiebox_client* client) {
  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  while (recv_message(client->conn_fd, &header, sizeof(header))) {
    if (reverse_handle_request(client, &header) == 0)
      break;
  }
  return;
}
static int reverse_handle_request(csiebox_client* client, csiebox_protocol_header* header) {
  if (header->req.magic != CSIEBOX_PROTOCOL_MAGIC_REQ) {
    return 0;
  }
  else {
    switch (header->req.op) {
      case CSIEBOX_PROTOCOL_OP_SYNC_META:
        fprintf(stderr, "reverse sync meta\n");
        csiebox_protocol_meta meta;
        if (complete_message_with_header(client->conn_fd, header, &meta)) {
          reverse_sync_file(client, &meta);
        }
        break;
      case CSIEBOX_PROTOCOL_OP_SYNC_END:
        fprintf(stderr, "reverse sync end\n");
        return 0;
      default:
        fprintf(stderr, "unknown op %x\n", header->req.op);
        break;
    }
    return 1;
  }
}
static void reverse_sync_file(csiebox_client* client, csiebox_protocol_meta* meta) {
  char* homedir = client->root;
  printf("homedir = %s\n", homedir);
  char bufpath[PATH_MAX], req_path[PATH_MAX];
  memset(bufpath, 0, PATH_MAX);
  memset(req_path, 0, PATH_MAX);
  recv_message(client->conn_fd, bufpath, meta->message.body.pathlen);

  fprintf(stderr, "rev = %s\n", bufpath);

  strcpy(req_path, homedir);
  strcat(req_path, "/");
  strcat(req_path, bufpath);
//  sprintf(req_path, "%s%s", homedir, buf); /* homedir and relative path */
  fprintf(stderr, "req_path: %s\n", req_path);
  free(homedir);
  free(bufpath);

  /* for attribe */
  struct stat stat;
  memset(&stat, 0, sizeof(struct stat)); 
  int need_data = 0, change = 0;
  if (lstat(req_path, &stat) < 0) { /* open path */
    need_data = 1;
    change = 1;
  } else {          
    if(stat.st_atime != meta->message.body.stat.st_atime || /* if two file/dir have different times, change to same time */
       stat.st_mtime != meta->message.body.stat.st_mtime){
      struct utimbuf* buf = (struct utimbuf*)malloc(sizeof(struct utimbuf)); /* utime type */
      buf->actime = meta->message.body.stat.st_atime;
      buf->modtime = meta->message.body.stat.st_mtime;
      
      double aseconds = difftime(stat.st_atime, buf->actime);
      double mseconds = difftime(stat.st_mtime, buf->modtime);

      if (aseconds > 0) 
	      buf->actime = stat.st_atime;
      if (mseconds > 0) {
	      buf->mtime = stat.st_atime;
        if(stat.st_mode != meta->message.body.stat.st_mode) { /* if two file/dir have different modes, change to same mode */ 
          chmod(req_path, meta->message.body.stat.st_mode);
        } 
      }

      if(utime(req_path, buf)!=0){
        printf("time fail\n");
      }
    }
           
    uint8_t hash[MD5_DIGEST_LENGTH];
    memset(hash, 0, MD5_DIGEST_LENGTH);
    if ((stat.st_mode & S_IFMT) == S_IFDIR) { /* if recv a dir */
    } else {
      md5_file(req_path, hash); /* if recv a file, check "now" hash of the file in sdir */
    }
    if (memcmp(hash, meta->message.body.hash, MD5_DIGEST_LENGTH) != 0) { /* two hash are diff, use memcmp */
      need_data = 1;
    }
  }

  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  header.res.magic = CSIEBOX_PROTOCOL_MAGIC_RES;
  header.res.op = CSIEBOX_PROTOCOL_OP_SYNC_META;
  header.res.datalen = 0;
  header.res.client_id = client->client_id;
  if (need_data) { /* if need data */
    header.res.status = CSIEBOX_PROTOCOL_STATUS_MORE;
  } else {
    header.res.status = CSIEBOX_PROTOCOL_STATUS_OK; /* void file or only change time or mode */
  }
  send_message(client->conn_fd, &header, sizeof(header));
  
  if (need_data) {
    csiebox_protocol_file file;
    memset(&file, 0, sizeof(file));
    recv_message(client->conn_fd, &file, sizeof(file));
    fprintf(stderr, "sync file: %zd\n", file.message.body.datalen);
    if ((meta->message.body.stat.st_mode & S_IFMT) == S_IFDIR) {
      fprintf(stderr, "dir\n");
      mkdir(req_path, DIR_S_FLAG);
    } else {
      fprintf(stderr, "regular file\n");
      int fd = open(req_path, O_CREAT | O_WRONLY | O_TRUNC, REG_S_FLAG);
      size_t total = 0, readlen = 0;;
      char buf[4096];
      memset(buf, 0, 4096);
      while (file.message.body.datalen > total) {
        if (file.message.body.datalen - total < 4096) {
          readlen = file.message.body.datalen - total;
        } else {
          readlen = 4096;
        }
        if (!recv_message(client->conn_fd, buf, readlen)) {
          fprintf(stderr, "file broken\n");
          break;
        }
        total += readlen;
        if (fd > 0) {
          write(fd, buf, readlen);
        }
      }
      if (fd > 0) {
        close(fd);
      }
    }
    if (change) {
      chmod(req_path, meta->message.body.stat.st_mode);
      struct utimbuf* buf = (struct utimbuf*)malloc(sizeof(struct utimbuf));
      buf->actime = meta->message.body.stat.st_atime;
      buf->modtime = meta->message.body.stat.st_mtime;
      utime(req_path, buf);
    }
    header.res.op = CSIEBOX_PROTOCOL_OP_SYNC_FILE;
    header.res.status = CSIEBOX_PROTOCOL_STATUS_OK; /* all recv finish and send OK*/
    send_message(client->conn_fd, &header, sizeof(header));
  }
}
