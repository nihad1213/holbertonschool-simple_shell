#include "shell.h"

/**
 * cd - Change directory
 * @arguments: Arguments
 * @inputStdin: Input
 * @exitStatus: Exit status
 * Return: Success
 */
int cd(char **arguments, char *inputStdin, int *exitStatus)
{
	int status;
	char cwd[128];

	getcwd(cwd, sizeof(cwd));

	(void)inputStdin;
	(void)exitStatus;

	/*HOME*/
	if (arguments[1] == NULL)
		status = chdir(_getenv("HOME"));
	/*User CD with -*/
	else if (strcmp(arguments[1], "-") == 0)
		/*Change to previous directory */
		status = chdir(_getenv("OLDPWD"));
	/*User cd with ~*/
	else if (strcmp(arguments[1], "~") == 0)
		/*Home*/
		status = chdir(_getenv("HOME"));
	else /*Specific Path*/
		status = chdir(arguments[1]);

	if (status == -1)
		perror("cd: error");

	setenv("OLDPWD", cwd, 1);

	setenv("PWD", getcwd(cwd, sizeof(cwd)), 1);
	return (1);
}

/**
 * setenvv - Adds or changes an environment variable
 * @arguments: Arguments
 * @inputStdin: Input from stdin
 * @exitStatus: Exit status
 * Return: Success
 */
int setenvv(char **arguments,  char *inputStdin, int *exitStatus)
{
	int numberTokens = 0;

	(void)inputStdin;
	(void)exitStatus;

	while (arguments[numberTokens] != NULL)
	{
		numberTokens++;
	}

	if (numberTokens == 3)
		setenv(arguments[1], arguments[2], 1);
	else
		fprintf(stderr, "incorrect format, use: \"setenv [KEY] [VALUE]\"\n");

	return (1);
}

/**
 * unsetenvv - Deletes an env var from the environment
 * @arguments: Arguments
 * @inputStdin: Input
 * @exitStatus: Exit status
 * Return: Success
 */
int unsetenvv(char **arguments,  char *inputStdin, int *exitStatus)
{
	int numberTokens = 0;

	(void)inputStdin;
	(void)exitStatus;

	while (arguments[numberTokens] != NULL)
	{
		numberTokens++;
	}

	if (numberTokens == 2)
		unsetenv(arguments[1]);
	else if (numberTokens != 2)
		fprintf(stderr, "incorrect format, use: \"unsetenv [KEY]\"\n");

	return (1);
}

/**
 * envv - Prints enviroment variable of current process
 * @arguments: Arguments
 * @inputStdin: Input
 * @exitStatus: exit status
 * Return: Success
 */
int envv(char **arguments, char *inputStdin, int *exitStatus)
{
	int i = 0;

	(void)arguments;
	(void)inputStdin;
	(void)exitStatus;

	if (environ[i] == NULL)
	{
		printf("%s\n", "The builtin env is empty");
		return (1);
	}

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (1);
}

/**
 * exitt - Function exits the shell
 * @arguments: Arguments
 * @inputStdin: Input
 * @exitStatus: exit status
 * Return: 0 on failure otherwise exits and returns
 * the exit status
 */
int exitt(char **arguments, char *inputStdin, int *exitStatus)
{
	int outputExit = 0;

	(void)arguments;
	(void)inputStdin;

	if (arguments[1] == NULL)
	{
		free(arguments);
		free(inputStdin);
		exit(*exitStatus);
	}

	if (arguments[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (0);
	}

	outputExit = atoi(arguments[1]);
	free(arguments);
	free(inputStdin);
	exit(outputExit);
}
