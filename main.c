#include "shell.h"

/**
 *main - Main loop help us to write command and execute it.
 *@argc: number of arguments
 *@argv: list of arguments
 *Return: SUCCESS
 */
int main(int argc, char *argv[])
{
	char **args = NULL;
	char *input = NULL;
	int statusReturn = 1;
	int exitStatus = 0;
	size_t size = 0; /*Size represent size of buffer*/
	ssize_t getLineReturn = 0;
	/*(void)argc and (void)argv is used to handle unused parameter error.*/
	(void) argc;
	(void) argv;
	/*Creating loop*/
	while (statusReturn && getLineReturn != EOF)
	{
		size = 0; /*set to 0 for every new input */
		/*Return 1 if the file in the argument refers to the terminal */
		statusReturn = isatty(STDIN_FILENO);
		if (statusReturn)
			write(STDOUT_FILENO, "$ ", 2);
		getLineReturn = getline(&input, &size, stdin);/*Get input from user*/
		if (getLineReturn == -1)/*-1 represent error*/
		{
			free(input);
			break;
		}
		/*If only spaces, tabs and line breaks are writed*/
		if (validateSpaces(input))
		{
			free(input);
			continue;
		}
		args = token(input); /*Divide input into tokens*/
		if (*args[0] == '\0') /*If we get only spaces, tabs and line breaks */
			continue;
		statusReturn = executeBuiltins(args, input, argv, &exitStatus);
		free(input);
		free(args);
	}
	return (EXIT_SUCCESS);
}
