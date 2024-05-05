#include "shell.h"

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
