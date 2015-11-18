#include "csiebox_server.h"

#include "csiebox_common.h"
#include "connect.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <utime.h>

static int parse_arg(csiebox_server* server, int argc, char** argv);
static void handle_request(csiebox_server* server, csiebox_protocol_header* header, int conn_fd);
static int get_account_info(csiebox_server* server,  const char* user, csiebox_account_info* info);
static void login(csiebox_server* server, int conn_fd, csiebox_protocol_login* login);
static void logout(csiebox_server* server, int conn_fd);
static void sync_file(csiebox_server* server, int conn_fd, csiebox_protocol_meta* meta);
static char* get_user_homedir(csiebox_server* server, csiebox_client_info* info);
static void rm_file(csiebox_server* server, int conn_fd, csiebox_protocol_rm* rm);

static char* convert_to_relative_path(csiebox_server* server, const char* path, int conn_fd);

/* reverse sync */
static int reverse_prepare_and_sync(csiebox_server* server, int conn_fd);
static void reverse_sync_all(csiebox_server* server, int conn_fd);
static void reverse_sync_file(csiebox_server* server, char* path, int conn_fd);
static csiebox_protocol_status reverse_sync_file_meta(csiebox_server* server, char* path, int conn_fd);
static void reverse_sync_file_data(csiebox_server* server, char* path, int conn_fd);
/* reverse sync end */

#define DIR_S_FLAG (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)//permission you can use to create new file
#define REG_S_FLAG (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)//permission you can use to create new directory

#define MAXFD 10

typedef struct conn {
  int length;
  struct sockaddr_in addr;
}Conn;


//read config file, and start to listen
void csiebox_server_init(
  csiebox_server** server, int argc, char** argv) {
  csiebox_server* tmp = (csiebox_server*)malloc(sizeof(csiebox_server));
  if (!tmp) {
    fprintf(stderr, "server malloc fail\n");
    return;
  }
  memset(tmp, 0, sizeof(csiebox_server));
  if (!parse_arg(tmp, argc, argv)) {
    fprintf(stderr, "Usage: %s [config file]\n", argv[0]);
    free(tmp);
    return;
  }
  int fd = server_start();
  if (fd < 0) {
    fprintf(stderr, "server fail\n");
    free(tmp);
    return;
  }
  tmp->client = (csiebox_client_info**)
      malloc(sizeof(csiebox_client_info*) * getdtablesize());
  if (!tmp->client) {
    fprintf(stderr, "client list malloc fail\n");
    close(fd);
    free(tmp);
    return;
  }
  memset(tmp->client, 0, sizeof(csiebox_client_info*) * getdtablesize());
  tmp->listen_fd = fd;
  *server = tmp;
}

//wait client to connect and handle requests from connected socket fd
int csiebox_server_run(csiebox_server* server) {
  printf("in server run\n");
  Conn conn[MAXFD];

  fd_set master; // master file descriptor list
  fd_set read_fds; // temp file descriptor list for select()
  int fdmax, newfd, conn_len;

  FD_ZERO(&master); // clear master and temp sets
  FD_ZERO(&read_fds);
  FD_SET(server->listen_fd, &master); // add listener to master set
  fdmax = server->listen_fd;

  while (1) {
    read_fds = master; // copy master

    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) { // remember +1
      perror("select");
      exit(4);
    }

    // find data need to read from current fd_set
    for(int i = 0; i <= fdmax; i++) {
      if (FD_ISSET(i, &read_fds)) { // find one
        if (i == server->listen_fd) { //create new fd

          struct sockaddr_in addr;
          memset(&addr, 0, sizeof(addr));
          conn_len = 0;
          newfd = accept(server->listen_fd, (struct sockaddr*)&addr, (socklen_t*)&conn_len);
          
	        if (newfd < 0) { //error
            if (errno == ENFILE) {
              fprintf(stderr, "out of file descriptor table\n");
              continue;
            } else if (errno == EAGAIN || errno == EINTR) {
              continue;
            } else {
              fprintf(stderr, "accept err\n");
              fprintf(stderr, "code: %s\n", strerror(errno));
              break;
            }
          } else {
            FD_SET(newfd, &master); // add to master set
            if (newfd > fdmax) fdmax = newfd;
          }
          memset(&(conn[newfd].addr), 0, sizeof(conn[newfd].addr));  
          conn[newfd].addr = addr;
          conn[newfd].length = conn_len;

        } else { // read data from client
          csiebox_protocol_header header;
          memset(&header, 0, sizeof(header));
  
          if (!recv_message(i, &header, sizeof(header))) { // logout
            fprintf(stderr, "end of connection\n");
            logout(server, i);
            close(i);
            FD_CLR(i, &master); //clear from master
          }
          else  handle_request(server, &header, i);
        }
      }
    }
  }
  return 1;
}

void csiebox_server_destroy(csiebox_server** server) {
  csiebox_server* tmp = *server;
  *server = 0;
  if (!tmp) {
    return;
  }
  close(tmp->listen_fd);
  int i = getdtablesize() - 1;
  for (; i >= 0; --i) {
    if (tmp->client[i]) {
      free(tmp->client[i]);
    }
  }
  free(tmp->client);
  free(tmp);
}

//read config file
static int parse_arg(csiebox_server* server, int argc, char** argv) {
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
  int accept_config_total = 2;
  int accept_config[2] = {0, 0};
  while ((keylen = getdelim(&key, &keysize, '=', file) - 1) > 0) {
    key[keylen] = '\0';
    vallen = getline(&val, &valsize, file) - 1;
    val[vallen] = '\0';
    fprintf(stderr, "config (%zd, %s)=(%zd, %s)\n", keylen, key, vallen, val);
    if (strcmp("path", key) == 0) {
      if (vallen <= sizeof(server->arg.path)) {
        strncpy(server->arg.path, val, vallen);
        accept_config[0] = 1;
      }
    } else if (strcmp("account_path", key) == 0) {
      if (vallen <= sizeof(server->arg.account_path)) {
        strncpy(server->arg.account_path, val, vallen);
        accept_config[1] = 1;
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



static void handle_request(csiebox_server* server, csiebox_protocol_header* header, int conn_fd) {
  if (header->req.magic != CSIEBOX_PROTOCOL_MAGIC_REQ) {
    return;
  }
  else {
    switch (header->req.op) {
      case CSIEBOX_PROTOCOL_OP_LOGIN:
        fprintf(stderr, "login\n");
        csiebox_protocol_login req;
        if (complete_message_with_header(conn_fd, header, &req)) {
          login(server, conn_fd, &req);
        }
        break;
      case CSIEBOX_PROTOCOL_OP_SYNC_META:
        fprintf(stderr, "sync meta\n");
        csiebox_protocol_meta meta;
        if (complete_message_with_header(conn_fd, header, &meta)) {
          sync_file(server, conn_fd, &meta);
        }
        break;
      case CSIEBOX_PROTOCOL_OP_SYNC_END:
        fprintf(stderr, "sync end\n");
        fprintf(stderr, "do reverse sync\n");
        reverse_prepare_and_sync(server, conn_fd);
        break;
      case CSIEBOX_PROTOCOL_OP_RM:
        fprintf(stderr, "rm\n");
        csiebox_protocol_rm rm;
        if (complete_message_with_header(conn_fd, header, &rm)) {
	        rm_file(server, conn_fd, &rm);        
        }
        break;
      default:
        fprintf(stderr, "unknown op %x\n", header->req.op);
        break;
    }
    return;
  }
}

//open account file to get account information
static int get_account_info(
  csiebox_server* server,  const char* user, csiebox_account_info* info) {
  FILE* file = fopen(server->arg.account_path, "r");
  
  if (!file) {
    return 0;
  }
  size_t buflen = 100;
  char* buf = (char*)malloc(sizeof(char) * buflen);
  memset(buf, 0, buflen);
  ssize_t len;
  int ret = 0;
  int line = 0;
  while ((len = getline(&buf, &buflen, file) - 1) > 0) {
    ++line;
    buf[len] = '\0';
    char* u = strtok(buf, ",");
    if (!u) {
      fprintf(stderr, "illegal form in account file, line %d\n", line);
      continue;
    }
    if (strcmp(user, u) == 0) {
      memcpy(info->user, user, strlen(user));
      char* passwd = strtok(NULL, ",");
      if (!passwd) {
        fprintf(stderr, "illegal form in account file, line %d\n", line);
        continue;
      }
      md5(passwd, strlen(passwd), info->passwd_hash);
      ret = 1;
      break;
    }
  }
  free(buf);
  fclose(file);
  return ret;
}

//handle the login request from client
static void login(
  csiebox_server* server, int conn_fd, csiebox_protocol_login* login) {
  int succ = 1;
  csiebox_client_info* info =
    (csiebox_client_info*)malloc(sizeof(csiebox_client_info));
  memset(info, 0, sizeof(csiebox_client_info));
  if (!get_account_info(server, login->message.body.user, &(info->account))) {
    fprintf(stderr, "cannot find account\n");
    succ = 0;
  }
  if (succ &&
      memcmp(login->message.body.passwd_hash,
             info->account.passwd_hash,
             MD5_DIGEST_LENGTH) != 0) {
    fprintf(stderr, "passwd miss match\n");
    succ = 0;
  }

  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  header.res.magic = CSIEBOX_PROTOCOL_MAGIC_RES;
  header.res.op = CSIEBOX_PROTOCOL_OP_LOGIN;
  header.res.datalen = 0;
  if (succ) {
    if (server->client[conn_fd]) {
      free(server->client[conn_fd]);
    }
    info->conn_fd = conn_fd;
    server->client[conn_fd] = info;
    header.res.status = CSIEBOX_PROTOCOL_STATUS_OK;
    header.res.client_id = info->conn_fd;
    char* homedir = get_user_homedir(server, info);
    mkdir(homedir, DIR_S_FLAG);
    free(homedir);
  } else {
    header.res.status = CSIEBOX_PROTOCOL_STATUS_FAIL;
    free(info);
  }
  send_message(conn_fd, &header, sizeof(header));
}

static void logout(csiebox_server* server, int conn_fd) {
  free(server->client[conn_fd]);
  server->client[conn_fd] = 0;
  close(conn_fd);
}

static void sync_file(csiebox_server* server, int conn_fd, csiebox_protocol_meta* meta) {
  csiebox_client_info* info = server->client[conn_fd];
  char* homedir = get_user_homedir(server, info);
  printf("homedir = %s\n", homedir);
  char buf[PATH_MAX], req_path[PATH_MAX];
  memset(buf, 0, PATH_MAX);
  memset(req_path, 0, PATH_MAX);
  recv_message(conn_fd, buf, meta->message.body.pathlen);
  sprintf(req_path, "%s%s", homedir, buf); /* homedir and relative path */
  free(homedir);
  fprintf(stderr, "req_path: %s\n", req_path);

  /* for attribe */
  struct stat stat;
  memset(&stat, 0, sizeof(struct stat)); 
  int need_data = 0, change = 0;
  if (lstat(req_path, &stat) < 0) { /* open path */
    need_data = 1;
    change = 1;
  } else {          
    if(stat.st_mode != meta->message.body.stat.st_mode) { /* if two file/dir have different modes, change to same mode */ 
      chmod(req_path, meta->message.body.stat.st_mode);
    }       

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
  header.res.client_id = conn_fd;
  if (need_data) { /* if need data */
    header.res.status = CSIEBOX_PROTOCOL_STATUS_MORE;
  } else {
    header.res.status = CSIEBOX_PROTOCOL_STATUS_OK; /* void file or only change time or mode */
  }
  send_message(conn_fd, &header, sizeof(header));
  
  if (need_data) {
    csiebox_protocol_file file;
    memset(&file, 0, sizeof(file));
    recv_message(conn_fd, &file, sizeof(file));
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
        if (!recv_message(conn_fd, buf, readlen)) {
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
    send_message(conn_fd, &header, sizeof(header));
  }
}

static char* get_user_homedir(csiebox_server* server, csiebox_client_info* info) {
  char* ret = (char*)malloc(sizeof(char) * PATH_MAX);
  memset(ret, 0, PATH_MAX);
  sprintf(ret, "%s/%s", server->arg.path, info->account.user);
  return ret;
}

static void rm_file(csiebox_server* server, int conn_fd, csiebox_protocol_rm* rm) {
  csiebox_client_info* info = server->client[conn_fd];
  char* homedir = get_user_homedir(server, info);
  char req_path[PATH_MAX], buf[PATH_MAX];
  memset(req_path, 0, PATH_MAX);
  memset(buf, 0, PATH_MAX);
  recv_message(conn_fd, buf, rm->message.body.pathlen);
  sprintf(req_path, "%s%s", homedir, buf);
  free(homedir);
  fprintf(stderr, "rm (%zd, %s)\n", strlen(req_path), req_path);
  struct stat stat;
  memset(&stat, 0, sizeof(stat));
  lstat(req_path, &stat);
  if ((stat.st_mode & S_IFMT) == S_IFDIR) {
    rmdir(req_path);
  } else {
    unlink(req_path);
  }

  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  header.res.magic = CSIEBOX_PROTOCOL_MAGIC_RES;
  header.res.op = CSIEBOX_PROTOCOL_OP_RM;
  header.res.datalen = 0;
  header.res.client_id = conn_fd;
  header.res.status = CSIEBOX_PROTOCOL_STATUS_OK;
  send_message(conn_fd, &header, sizeof(header));
}


/* reverse sync */
static int reverse_prepare_and_sync(csiebox_server* server, int conn_fd) {
  csiebox_client_info* info = server->client[conn_fd];
  char* homedir = get_user_homedir(server, info);

  if (chdir(homedir) != 0) {
    fprintf(stderr, "invalid server path\n");
    free(homedir);
    return 0;
  }
  fprintf(stderr, "cwd = %s\n", homedir);
  reverse_sync_all(server, conn_fd);
    
  csiebox_protocol_header header;
  memset(&header, 0, sizeof(header));
  header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_END;
  header.req.client_id = conn_fd;
  send_message(conn_fd, &header, sizeof(header));
  chdir(homedir);
  free(homedir);
  return 1;
}

static void reverse_sync_all(csiebox_server* server, int conn_fd) {
  char* cwd = (char*)malloc(sizeof(char) * PATH_MAX);
  memset(cwd, 0, sizeof(char) * PATH_MAX);
  if (getcwd(cwd, PATH_MAX) == 0) {
    fprintf(stderr, "getcwd fail\n");
  }

  fprintf(stderr, "in reverse_sync_all, cwd =  %s\n", cwd);

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
    reverse_sync_file(server, file->d_name, conn_fd);
    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      if (chdir(file->d_name) != 0) {
        fprintf(stderr, "bad dir %s\n", file->d_name);
        continue;
      }
      reverse_sync_all(server, conn_fd); /* go to next level */
      chdir(cwd);
    }
  }
  closedir(dir);
  free(cwd);
  return;
}

static void reverse_sync_file(csiebox_server* server, char* path, int conn_fd) {
  csiebox_protocol_status status;
  status = reverse_sync_file_meta(server, path, conn_fd);
  if (status == CSIEBOX_PROTOCOL_STATUS_MORE) {
    reverse_sync_file_data(server, path, conn_fd);
  }
}

static csiebox_protocol_status reverse_sync_file_meta(csiebox_server* server, char* path, int conn_fd) {
// change!!
//  char* relative = convert_to_relative_path(server, path, conn_fd);
//  if (!relative) {
//    fprintf(stderr, "convert relative fail: %s\n", path);
//    return CSIEBOX_PROTOCOL_STATUS_FAIL;
//  }
//haven't 

  csiebox_protocol_meta meta;
  memset(&meta, 0, sizeof(meta));
  meta.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  meta.message.header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_META;
  meta.message.header.req.client_id = conn_fd;
  meta.message.header.req.datalen = sizeof(meta) - sizeof(csiebox_protocol_header);
//  meta.message.body.pathlen = strlen(relative);
  meta.message.body.pathlen = strlen(path);
  lstat(path, &(meta.message.body.stat));
  if ((meta.message.body.stat.st_mode & S_IFMT) == S_IFDIR) { /* dir: do nothing */
  } else {
    md5_file(path, meta.message.body.hash); /* file: send a hash */
  }
  send_message(conn_fd, &meta, sizeof(meta));
//  send_message(conn_fd, relative, strlen(relative));
  send_message(conn_fd, path, strlen(path));
//  free(relative);
  
  csiebox_protocol_header header;
  recv_message(conn_fd, &header, sizeof(header));
  if (header.res.status == CSIEBOX_PROTOCOL_STATUS_FAIL) {
    fprintf(stderr, "sync meta fail: %s\n", path);
    return;
  }
  return header.res.status;
}

static void reverse_sync_file_data(csiebox_server* server, char* path, int conn_fd) {
  fprintf(stderr, "file_data: %s\n", path);
  struct stat stat;
  memset(&stat, 0, sizeof(stat));
  lstat(path, &stat);
  csiebox_protocol_file file;
  memset(&file, 0, sizeof(file));
  file.message.header.req.magic = CSIEBOX_PROTOCOL_MAGIC_REQ;
  file.message.header.req.op = CSIEBOX_PROTOCOL_OP_SYNC_FILE;
  file.message.header.req.client_id = conn_fd;
  file.message.header.req.datalen = sizeof(file) - sizeof(csiebox_protocol_header);
  if ((stat.st_mode & S_IFMT) == S_IFDIR) {
    file.message.body.datalen = 0;
    fprintf(stderr, "dir datalen: %zu\n", file.message.body.datalen);
    send_message(conn_fd, &file, sizeof(file));
  } else {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
      fprintf(stderr, "open fail\n");
      file.message.body.datalen = 0;
      send_message(conn_fd, &file, sizeof(file));
    } else {
      file.message.body.datalen = lseek(fd, 0, SEEK_END);
      fprintf(stderr, "else datalen: %zd\n", file.message.body.datalen);
      send_message(conn_fd, &file, sizeof(file));
      lseek(fd, 0, SEEK_SET);
      char buf[4096];
      memset(buf, 0, 4096);
      size_t readlen;
      while ((readlen = read(fd, buf, 4096)) > 0) {
        send_message(conn_fd, buf, readlen);
      }
      close(fd);
    }
  }
  csiebox_protocol_header header;
  recv_message(conn_fd, &header, sizeof(header));
  if (header.res.status != CSIEBOX_PROTOCOL_STATUS_OK) {
    fprintf(stderr, "sync data fail: %s\n", path);
  }
}

static char* convert_to_relative_path(csiebox_server* server, const char* path, int conn_fd) {
  csiebox_client_info* info = server->client[conn_fd];
  char* homedir = get_user_homedir(server, info);

  char* ret = (char*)malloc(sizeof(char) * PATH_MAX);
  if (path[0] == '/') {
    strcpy(ret, path);
  } else {
    char dir[PATH_MAX];
    memset(dir, 0, PATH_MAX);
    getcwd(dir, PATH_MAX);
    sprintf(ret, "%s/%s", dir, path);
  }
  if (strncmp(homedir, ret, strlen(homedir)) != 0) {
    free(ret);
    return NULL;
  }
  size_t rootlen = strlen(homedir);
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
