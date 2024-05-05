#include "shell.h"

/**
 *token - Divide input into tokens
 *@input: Input
 *Return: Tokens
 */
char **token(char *input)
{
	char **tokens = NULL, *token = NULL;
	int buffer = BUFFER_SIZE, newBuffer = 0, position = 0;
	char **backup_tokens = NULL;

	/*allocate memory for the array of tokens */
	tokens = malloc(buffer * sizeof(char *));

	if (tokens == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer)
		{
			newBuffer = BUFFER_SIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, newBuffer * sizeof(char *));

			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS);
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 *tokenPath - Divide Path into tokens
 *@input: Input
 *Return: Tokens
 */
char **tokenPath(char *input)
{
	int buffer = BUFFER_SIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backup_tokens = NULL;

	/*allocate memory for the array of tokens */
	tokens = malloc(buffer * sizeof(char *));

	if (tokens == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, ":");

	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		/*reallocate the array of tokens if necessary*/
		if (position >= buffer)
		{
			newBuffer = BUFFER_SIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, ":");
	}

	tokens[position] = NULL;
	return (tokens);
}
