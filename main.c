#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UnixLs.h"

int main(int argc, char* argv[]) {
    bool lsl = false;
    bool lsi = false;
    char* dir = NULL;
    bool multiFile = false;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (*(argv[i]) == '-') {
                for (int charIndex = 1; charIndex < strlen(argv[i]); charIndex++) {
                    if (*(argv[i] + charIndex) == 'l') {
                        lsl = true;
                    } else if (*(argv[i] + charIndex) == 'i') {
                        lsi = true;
                    } else {
                        printf("Invalid option for ls command. Please try again!!\n");
                        exit(1);
                    }
                }
            } else {
                if (i + 1 < argc) {
                    multiFile = true;
                }

                dir = argv[i];
                if (multiFile) {
                    printf("%s:\n", dir);
                }
                lsCommand(lsl, lsi, dir);
            }
        }

        if (dir == NULL) {
            lsCommand(lsl, lsi, ".");
        }

    } else {
        lsCommand(lsl, lsi, ".");
    }
}