#include "shell.h"

/**
 * execute - Fork process and replace the child
 * with a new program
 * @arguments: Arguments
 * @argv: Array of arguments
 * @exitStatus: Exit status
 * Return: Always 1 (success)
 */
int execute(char **arguments, char **argv, int *exitStatus)
{
	pid_t pid;
	int status;
	char *newArguments;

	newArguments = validateInput(arguments, argv);
	if (strcmp(newArguments, "Fail access") == 0)
		return (1);
	pid = fork();
	if (pid == 0) /*Current child process*/
	{
		if (execve(newArguments, arguments, environ) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) /*fork fail*/
	{
		perror("Error forking");
		free(newArguments);
		return (1);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			*exitStatus = WEXITSTATUS(status);
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
			free(newArguments);
		return (1);
	}
	return (1);
}

/**
 * executeBuiltins - Choose from an array of builtin functions
 *
 * @arguments: Arguments (tokens)
 * @inputStdin: String from input
 * @argv: Array of arguments
 * @exitStatus: Exit status
 *
 * Return: Status to stay or exit the main loop,
 * 1 or 0
 */
int executeBuiltins(char **arguments, char *inputStdin,
					char **argv, int *exitStatus)
{
	int i = 0;

	choose_builtins_t options[] = {
		{"exitt", exitt},
		{"envv", envv},
		{"cd", cd},
		{"setenvv", setenvv},
		{"unsetenvv", unsetenvv},
		{NULL, NULL}
	};

	while (options[i].nameBuiltin)
	{
		/* compare if arguments[0] matches the builtin function name */
		if (strcmp(options[i].nameBuiltin, arguments[0]) == 0)
		{
			/* return the pointer to function (2nd memeber of array) and execute it */
			return ((int)((*options[i].func_builtin)(arguments, inputStdin, exitStatus)));
		}
		i++;
	}
	return (execute(arguments, argv, exitStatus));
}
