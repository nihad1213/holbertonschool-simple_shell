#include "shell.h"

/**
 *execute - Fork process and replace the child
 *with a new program
 *@args: String of arguments (tokens)
 *@argv: Array of arguments
 *@exitStatus: Exit status
 *Return: 1
 */
int execute(char **args, char **argv, int *exitStatus)
{
	pid_t pid;
	/*It using for waitpid syscall*/
	int status;
	char *new_args;

	new_args = validateInput(args, argv);
	(void) exitStatus;
	if (strcmp(new_args, "Fail access") == 0)
		return (1);
	/*Fork create new process*/
	pid = fork();
	/*0 means child process*/
	if (pid == 0)
	{
		if (execve(new_args, args, environ) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	/*<0 means error in fork*/
	else if (pid < 0)
	{
		perror("Error forking");
		free(new_args);
		return (1);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			*
			exitStatus = WEXITSTATUS(status);
		if (args[0][0] != '/' && args[0][0] != '.')
			free(new_args);
		return (1);
	}
	return (1);
}

/**
 *executeBuiltins - Choose from an array of builtin functions
 *@args: Arguments
 *@inputStdin: Input
 *@argv: List of arguments
 *@exitStatus: Exit status
 *Return: 1 or 0
 */
int executeBuiltins(char **args,
	char *inputStdin,
	char **argv,
	int *exitStatus)
{
	int i = 0;
	chooseBuiltins options[] = {
		{ "exit", exitt},
		{ "env", envv},
		{ "cd", cd},
		{ "setenv", setenvv},
		{ "unsetenv", unsetenvv},
		{NULL, NULL}
	};
	while (options[i].nameBuiltin)
	{
		if (strcmp(options[i].nameBuiltin, args[0]) == 0)
		{
			return ((int)((*options[i].functionBuiltin)(args, inputStdin, exitStatus)));
		}

		i++;
	}
	return (execute(args, argv, exitStatus));
}
