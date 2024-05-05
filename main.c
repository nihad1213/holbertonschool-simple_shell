#include "shell.h"

/**
 * main - Main loop help us to write command and execute it.
 * @argc: number of arguments
 * @argv: list of arguments
 * Return: SUCCESS  
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
    (void)argc;
    (void)argv;

    /*Creating loop*/
    while (statusReturn && getLineReturn != EOF)
    {
        size = 0; /* set to 0 for every new input */

		/*Return 1 if the file in the argument refers to the terminal */
		statusReturn = isatty(STDIN_FILENO);

		if (statusReturn)
            /*Write $ in buffer*/
			write(STDOUT_FILENO, "$ ", 2);
        
        /*Get input from user*/
		getLineReturn = getline(&input, &size, stdin);
		
        /*-1 represent error*/
        if (getLineReturn == -1)
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
		
        /*Divide input into tokens*/
		args = token(input);
		if (*args[0] == '\0') /*If we get only spaces, tabs and line breaks */
			continue;
		
        statusReturn = executeBuiltins(args, input, argv, &exitStatus);
		free(input);
		free(args);
	}

	return (EXIT_SUCCESS);
}
