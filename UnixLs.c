#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <libgen.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include "UnixLs.h"

void lsCommand(bool lsl, bool lsi, char* directory) {
    struct stat buf;
    struct dirent *dp;
    DIR* dir = opendir(directory);

    // if (dir == NULL) {
    //     if (lstat())
    // }

    dp = readdir(dir);
    while (dp) {
        char dirName[51200];
        memset(&dirName, 0, 51200);
        strcpy(dirName, directory);
        if (strcmp(directory, "/")) {
            strcat(dirName, "/");
        }
        strcat(dirName, (char*)dp->d_name);
        if (lstat(dirName, &buf) == 0) {
            if (lsi) {
            printf("%ju ", (uintmax_t)buf.st_ino);
            }
            if (lsl) {
                // Paul
            }
            printf("%s", dp->d_name);
            if (lsl && (buf.st_mode & S_IFMT) == S_IFLNK) {
                memset(&buf, 0, sizeof(struct stat));
                stat(dirName, &buf);
                char path[51200];
                memset(&path, 0, 51200);
                readlink(dirName, path, 51200);
                printf(" -> %s", path);
            }
            printf("\n");   
		}
        dp = readdir(dir);
    }
}