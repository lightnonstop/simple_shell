#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

extern char **environ;
char *_which(char *file);
int _strcmp(const char *str1, const char *str2);
void exit_m(pid_t pid);
char *_strtok(char *str, const char *delim);

#endif /* End of MAIN_H */

