#include "shell.h"

/**
 * token - Divide the input into arguments
 * @input: Input
 * Return: Pointer
 */
char **token(char *input)
{
	char **tokens = NULL, *token = NULL;
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **backupTokens = NULL;

	tokens = malloc(buffer * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backupTokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backupTokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * tokeniPath - Split the environment variable PATH into an array of tokens
 * @input: Pointer to environment variable PATH
 * Return: Pointer to the array of tokens
 */
char **tokenPath(char *input)
{
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backupTokens = NULL;

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
		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backupTokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backupTokens);
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
