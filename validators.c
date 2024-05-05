#include "shell.h"

/**
* validateInput - Validates if the PATH exists
* @args: String of Tokens
* @argv: String of arguments from input
* Return: A pointer to an array of the tokenized PATH directories
*/
char *validateInput(char **args, char **argv) /* */
{
	char *new_args, *first, *slash_argument = "/";
	char **tokens_path, holder_env[1024];
	int i = 0;

	/* check first element in array if starts with "." or*/
	/*"/" character if so assumes arg is a path or executable file*/
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		/* point to the same address */
		new_args = args[0];

		/* check if file exists if not it points to error message */
		if ((access(new_args, F_OK) == -1))
		{
			/* returns this message as error if file or path doesnt exist */
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			argv[0], __LINE__, args[0]);

			return ("Fail access");
		}
	}
	else
	{
		/* get PATH and copy it to holder_env buffer*/
		strcpy(holder_env, getenv("PATH"));

		/* tokenize holer_env into array of directory PATH environment string */
		tokens_path = token(holder_env);
		while (tokens_path[i])
		{
			/* checkking if file exists if not frees allocated memory*/
			/*for the full path and continues to next directory*/
			first = str_concat(slash_argument, args[0]);
			new_args = str_concat(tokens_path[i], first);
			if ((access(new_args, F_OK) == -1))
			{
				free(new_args);
				free(first);
			}
			else
			{
				free(tokens_path);
				free(first);
				return (new_args);
			}
			i++;
		}
		free(tokens_path);
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
		argv[0], __LINE__, args[0]);

		return ("Fail access");
	}
	return (new_args);
}

/**
* validateSpace - Checks if input is only spaces
* @input: string from input
* Return: 0 if there are spaces, tabs or line breaks
*/
int validateSpace(char *input)
{
	int i = 0, flag = 1, len = 0;

	len = strlen(input);

	while (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
		i++;

	if (i != len)
		flag = 0;
	return (flag);
}
