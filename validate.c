#include "shell.h"

/**
 *validate_input - Validates if the PATH exists
 *@args: Tokens
 *@argv: List of Arguments
 *Return: new_args
 */
char *validateInput(char **args, char **argv)
{
	char *new_args, *first, *slash_argument = "/", **tokens_path, holder_env[1024];
	/*char **tokens_path, holder_env[1024];*/
	int i = 0;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		new_args = args[0];
		if ((access(new_args, F_OK) == -1))
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				argv[0], __LINE__, args[0]);
			return ("Fail access");
		}
	}
	else
	{
		strcpy(holder_env, getenv("PATH"));
		tokens_path = tokenPath(holder_env);
		while (tokens_path[i])
		{
			first = strcat(slash_argument, args[0]);
			new_args = strcat(tokens_path[i], first);
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
 *validateSpaces- Checks if input is only spaces
 *@input: Input
 *Return: flag
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
