#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char **env);
void _execute(char *arguments, struct stat *statbuf, char **envp);
bool check_file_status(char *pathname, struct stat *statbuf);

#endif /* SHELL_H */
