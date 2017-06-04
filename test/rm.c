#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define PATH_MAX 1000


// int rm(char path[PATH_MAX])
// {
// 	DIR *d = opendir(path);
// 	size_t path_len = strlen(path);
// 	int r = -1;

// 	if (d) {
// 	  	struct dirent *p;
// 	  	r = 0;

// 		while (!r && (p=readdir(d))) {
// 			int r2 = -1;
// 			char *buf;
// 			size_t len;

// 		/* Skip the names "." and ".." as we don't want to recurse on them. */
// 			if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))	continue;

// 			len = path_len + strlen(p->d_name) + 2; 
// 			buf = malloc(len);

// 			if (buf) {
// 				struct stat statbuf;
// 				printf("path = %s\n", p->d_name);
// 				snprintf(buf, len, "%s/%s", path, p->d_name);

// 				if (!stat(buf, &statbuf)) {
// 					if (S_ISDIR(statbuf.st_mode)) {
// 		   				r2 = rm(buf);
// 					}
// 					else {
// 		   				r2 = unlink(buf);
// 					}
// 				}

// 				free(buf);
// 			}
// 			r = r2;
// 		}
// 		closedir(d);
// 	}
// 	if (!r) {
// 		r = rmdir(path);
// 	}
// 	return r;
// }


void rm(char *dir)
{
	DIR *dp = opendir(dir);
	struct dirent *entry;
	struct stat statbuf;

	if (dp == NULL) {
		fprintf(stderr, "can't open directroy: %s\n", dir);
		return;
	}
	chdir(dir);

	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			rm(entry->d_name);
		}
		else rm(entry->d_name);
	}

	rmdir(entry->d_name);
	chdir("..");
	closedir(dp);
}


void delete_folder_tree (const char* directory_name) {
    DIR*            dp;
    struct dirent*  ep;
    char            p_buf[512] = {0};

    dp = opendir(directory_name);

    while ((ep = readdir(dp)) != NULL) {
        sprintf(p_buf, "%s/%s", directory_name, ep->d_name);
        if (path_is_directory(p_buf))
            delete_folder_tree(p_buf);
        else
            unlink(p_buf);
    }

    closedir(dp);
    rmdir(directory_name);
}

int path_is_directory (const char* path) {
    struct stat s_buf;

    if (stat(path, &s_buf))
        return 0;

    return S_ISDIR(s_buf.st_mode);
}

int main()
{
	char path[] = "./b";
	rm(path);
	return 0;
}