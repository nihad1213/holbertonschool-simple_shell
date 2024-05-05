#include "shell.h"

/**
* validateInput - Validates if the PATH exists
* @arguments: Arguments
* @argv: Arguments from input
* Return: A pointer to an array of the tokenized PATH directories
*/
char *validateInput(char **arguments, char **argv) /* */
{
	char *newArguments, *first, *slashArgument = "/";
	char **tokensPath, holderEnv[1024];
	int i = 0;

	/* check first element in array if starts with "." or*/
	/*"/" character if so assumes arg is a path or executable file*/
	if (arguments[0][0] == '/' || arguments[0][0] == '.')
	{
		/* point to the same address */
		newArguments = arguments[0];

		/* check if file exists if not it points to error message */
		if ((access(newArguments, F_OK) == -1))
		{
			/* returns this message as error if file or path doesnt exist */
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			argv[0], __LINE__, arguments[0]);

			return ("Fail access");
		}
	}
	else
	{
		/* get PATH and copy it to holderEnv buffer*/
		strcpy(holderEnv, _getenv("PATH"));

		tokensPath = tokenPath(holderEnv);
		while (tokensPath[i])
		{
			first = str_concat(slashArgument, arguments[0]);
			newArguments = str_concat(tokensPath[i], first);
			if ((access(newArguments, F_OK) == -1))
			{
				free(newArguments);
				free(first);
			}
			else
			{
				free(tokensPath);
				free(first);
				return (newArguments);
			}
			i++;
		}

		free(tokensPath);
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
		argv[0], __LINE__, arguments[0]);

		return ("Fail access");
	}
	return (newArguments);
}

/**
* validateSpaces - Checks if input is only spaces
* @input: string from input
* Return: 0
*/
int validateSpaces(char *input)
{
	int i = 0, flag = 1, len = 0;

	len = strlen(input);

	while (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
		i++;

	if (i != len)
		flag = 0;

	return (flag);
}
