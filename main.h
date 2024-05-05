#ifndef MAIN_H
#define MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
char **line_div(char *command,char **arr);
char *_getline(void);
int execute(char *command);
void execute_child(char *command);
int execute_parent(pid_t pid);
void print_environment();
void execute_absolute_path(char *arr[]);
void execute_relative_path(char *arr[]);
extern char **environ;
int main(void);
#endif
