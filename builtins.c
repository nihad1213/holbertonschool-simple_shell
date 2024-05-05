#include "shell.h"

/**
 * cd - Change directory
 *
 * @args: tokens
 * @inputStdin: Input
 * @exitStatus: Exit
 * Return: SUCCESS
 */
int cd(char **args, char *inputStdin, int *exitStatus)
{

    /*Store return value of chdir() syscall*/
    int status;
	char cwd[128];

    /*Handle unused parameter error*/
    (void)inputStdin;
    (void)exitStatus;

	getcwd(cwd, sizeof(cwd));

    /*Home Directory*/
	if (args[1] == NULL)
		status = chdir(getenv("HOME"));
    /*Get Back Directory*/
	else if (strcmp(args[1], "-") == 0)
		status = chdir(getenv("OLDPWD"));
	/*Get Back Home Directory*/
	else if (strcmp(args[1], "~") == 0)
		status = chdir(getenv("HOME"));
	/*Get Specific Path*/
    else
		status = chdir(args[1]);

	/*Error Handling*/
	if (status == -1)
		perror("cd: error");

	setenv("OLDPWD", cwd, 1);

	setenv("PWD", getcwd(cwd, sizeof(cwd)), 1);
	return (1);
}

/**
 * setenv - Adds or changes an environment variable
 * @args: Tokens
 * @inputStdin: Input
 * @exitStatus: Exit status
 * Return: SUCCESS
 */
int setenvv(char **args,  char *inputStdin, int *exitStatus)
{

	int numberTokens = 0;

    /*Error handling*/
    (void)inputStdin;
	(void)exitStatus;

	while (args[numberTokens] != NULL)
	{
		numberTokens++;
	}

	if (numberTokens == 3)
		setenv(args[1], args[2], 1);

	else
		fprintf(stderr, "incorrect format, use: \"setenv [KEY] [VALUE]\"\n");

	return (1);
}

/**
 * unsetenv - Deletes an env var from the environment
 * @args: Tokens
 * @inputStdin: Input
 * @exitStatus: Exit status
 *
 * Return: SUCCESS
 */
int unsetenvv(char **args,  char *inputStdin, int *exitStatus)
{
    int numberTokens = 0;

    /*Error handling*/
	(void)inputStdin;
	(void)exitStatus;

	while (args[numberTokens] != NULL)
	{
		numberTokens++;
	}

	if (numberTokens == 2)
        unsetenv(args[1]);        
	else if (numberTokens != 2)
		fprintf(stderr, "incorrect format, use: \"unsetenv [KEY]\"\n");

	return (1);
}

/**
 * env - Prints enviroment variable of current process
 * @args: arguments
 * @inputStdin: input of stdin
 * @exitStatus: exit status
 * Return: 1
 */
int envv(char **args, char *inputStdin, int *exitStatus)
{
	int i = 0;

    /*Error handling*/
	(void)args;
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
 * @args: arguments
 * @inputStdin: input of stdin
 * @exitStatus: exit status
 * Return: 0 on failure
 */
int exitt(char **args, char *inputStdin, int *exitStatus)
{
    /*Store return value of exit*/
	int outputExit = 0;

    /*Error handling*/
	(void)args;
	(void)inputStdin;

	if (args[1] == NULL)
	{
		free(args);
		free(inputStdin);
		exit(*exitStatus);
	}

	if (args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (0);
	}


	outputExit = atoi(args[1]);
	free(args);
	free(inputStdin);
	exit(outputExit);
}
