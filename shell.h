#ifndef SHELL_H
#define SHELL_H

/*SYSTEM HEADER FILES START*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
/*SYSTEM HEADER FILES END*/

/*CONSTANTS START*/
#define BUFSIZE 256
#define DELIM " \t\n"
/*CONSTANTS END*/

/**
 * struct choose_builtin - Builtin commands struct
 * @nameBuiltin: Name of builtin command
 * @func_builtin: Pointer to builtin command functions
 */
typedef struct choose_builtin
{
	char *nameBuiltin;
	int (*func_builtin)(char **, char *, int *);
} choose_builtins_t;

extern char **environ;

/*FUNCTION PRORTYPES START*/
int execute(char *arguments[], char *argv[], int *exitStatus);
int executeBuiltins(char *arguments[], char *inputStdin,
		char *argv[], int *exitStatus);

char *validateInput(char *arguments[], char *argv[] __attribute__((unused)));
int validateSpaces(char *input);

char **token(char *input);
char **tokenPath(char *input);

int cd(char *arguments[], char *inputStdin, int *exitStatus);
int setenvv(char *arguments[],  char *inputStdin, int *exitStatus);
int unsetenvv(char **arguments,  char *inputStdin, int *exitStatus);
int envv(char **arguments, char *inputStdin, int *exitStatus);
int exitt(char **arguments, char *inputStdin, int *exitStatus);

char *str_concat(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
/*FUNCTION PRORTYPES END*/
#endif
