#ifndef MAINH
#define MAINH
#define PATH "PATH="
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **path_var;
extern char **environ;
char **get_command(char **);
char **get_path(char **);
char *find_file(char *command, int *);
void print_env(void);
void print_prompt(int status);
void free_path(void);
int exec_c(char **fcommand);
char **_strtok(char *str, char delim);
char *custom_getline(void);
char *custom_strdup(const char *src);
int custom_strcmp(const char *s1, const char *s2);
size_t custom_strlen(const char *s);
int arg_counter(char *buf, int size);
int custom_atoi(const char *str);
long custom_strtol(const char *str, char **endptr, int base);
int main_helper(char **fcommand, int status, char *buf, char **argv);

#endif
