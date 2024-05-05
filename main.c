#include "shell.h"

/**
* main - Main loop that tokenize input and execute commands
* @argc: Number of arguments
* @argv: List of arguments
* Return: 0
*/

int main(int argc, char *argv[])
{
	char **arguments = NULL;
	char *inputStdin = NULL;
	int statusReturn = 1, exitStatus = 0;
	size_t size = 0;
	ssize_t returnValue = 0;
    (void)argc;
    (void)argv;

    /*loop start*/
    while (statusReturn && returnValue != EOF)
	{
		size = 0;
        /*isatty() - Check relation between terminal*/
		statusReturn = isatty(STDIN_FILENO);
		if (statusReturn)
			write(STDOUT_FILENO, "$ ", 2);
		returnValue = getline(&inputStdin, &size, stdin);
		if (returnValue == -1) /*error Case*/
		{
			free(inputStdin);
			break;
		}
		if (validateSpaces(inputStdin))
		{
			free(inputStdin);
			continue;
		}
		arguments = token(inputStdin);
		if (*arguments[0] == '\0')
			continue;
		statusReturn = executeBuiltins(arguments, inputStdin,
		argv, &exitStatus);
		free(inputStdin);
		free(arguments);
	}
	return (0);
}
