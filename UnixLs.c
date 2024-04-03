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
# include "infodemo.h"


void file_mode_to_string(mode_t mode, char str[]) {
    if (S_ISREG(mode)) {
        str[0] = '-';
    } else if (S_ISDIR(mode)) {
        str[0] = 'd';
    } else if (S_ISLNK(mode)) {
        str[0] = 'l';
    } else {
        str[0] = '?';
    }

    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    if (mode & S_ISUID) {
        str[3] = (mode & S_IXUSR) ? 's' : 'S'; 
    } else {
        str[3] = (mode & S_IXUSR) ? 'x' : '-';
    }

    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    if (mode & S_ISGID) {
        str[6] = (mode & S_IXGRP) ? 's' : 'S'; 
    } else {
        str[6] = (mode & S_IXGRP) ? 'x' : '-';
    }

    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    if (mode & S_ISVTX) {
        str[9] = (mode & S_IXOTH) ? 't' : 'T';
    } else {
        str[9] = (mode & S_IXOTH) ? 'x' : '-';
    }

    
    str[10] = '\0';
}

void lsCommand(bool lsl, bool lsi, char* directory) {
    struct stat buf;
    struct dirent *dp;
    DIR* dir = opendir(directory);

    if (dir == NULL) {
        printf("Cannot open file directory. Please try again!!\n");
        return;
    }

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

                char mode[11]; // 10 characters for permissions + null terminator
                file_mode_to_string(buf.st_mode, mode);
                printf("%s ", mode); 
                printf(" %2ld ", buf.st_nlink);
                
                getAndPrintUserName(buf.st_uid);
                
                getAndPrintGroup(buf.st_gid);
                printf(" %5ld ", buf.st_size);
                struct tm date = *(localtime(&buf.st_mtime));

                if (date.tm_mon == 0) {
                    printf("Jan ");
                } else if (date.tm_mon == 1) {
                    printf("Feb ");
                } else if (date.tm_mon == 2) {
                    printf("Mar ");
                } else if (date.tm_mon == 3) {
                    printf("Apr ");
                } else if (date.tm_mon == 4) {
                    printf("May ");
                } else if (date.tm_mon == 5) {
                    printf("Jun ");
                } else if (date.tm_mon == 6) {
                    printf("Jul ");
                } else if (date.tm_mon == 7) {
                    printf("Aug ");
                } else if (date.tm_mon == 8) {
                    printf("Sep ");
                } else if (date.tm_mon == 9) {
                    printf("Oct ");
                } else if (date.tm_mon == 10) {
                    printf("Nov ");
                } else {
                    printf("Dec ");
                }

                printf("%2d %d ", date.tm_mday, date.tm_year + 1900);

                printf("%d:", date.tm_hour);
                if (date.tm_min < 10) {
                    printf("0");
                }
                printf("%d ", date.tm_min);

                
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
    printf("\n");
}