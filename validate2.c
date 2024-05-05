#include "shell.h"

/**
 *validateInput - Validates if the PATH exists
 *@args: Tokens
 *@argv: List of Arguments
 *Return: new_args
 */
char *validateInput(char **args, char **argv)
{
	char *new_args, *first, *slash_argument = "/";
	char **tokens_path, holder_env[1024];
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

		tokens_path = tokenholder_env);
		while (tokens_path[i])
		{
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
