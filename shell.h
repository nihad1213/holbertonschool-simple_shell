#ifndef SHELL_H
#define SHELL_H

/*SYSTEM HEADER FILES START*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

/*SYSTEM HEADER FLES END*/

/*CONSTANTS START*/
#define BUFFER_SIZE 100
#define DELIMITERS " \t\n"
/*CONSTANTS END*/

/**
 *struct chooseBuiltin - Builtin functions in in struct
 *@nameBuiltin: Name of builtin functions
 *@functionBuiltin: Pointer to builtin functions
 */
typedef struct chooseBuiltin
{
	char *nameBuiltin;
	int (*functionBuiltin)(char **, char *, int *);
}

chooseBuiltins;

/*Glabol variable to access the environment list*/
extern char **environ;

/*FUNCTION PROTOTYPES START*/
int cd(char **args, char *inputStdin, int *exitStatus);
int setenvv(char **args, char *inputStdin, int *exitStatus);
int unsetenvv(char **args, char *inputStdin, int *exitStatus);
int envv(char **args, char *inputStdin, int *exitStatus);
int exitt(char **args, char *inputStdin, int *exitStatus);
int execute(char **args, char **argv, int *exitStatus);
int executeBuiltins(	char **args,
	char *inputStdin,
	char **argv,
	int *exitStatus);
char **token(char *input);
char **tokenPath(char *input);
char *validateInput(char **args, char **argv);
int validateSpaces(char *input);
char *str_concat(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
/*FUNCTION PROTOTYPES END*/
#endif
