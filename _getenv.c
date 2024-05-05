#include "shell.h"
/**
 * _getenv - gets the path
 * @path_name: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 */
char *_getenv(char *pathName)
{
	char **environCursor, *envPtr, *namePtr;

	environCursor = environ;
	while (*environCursor)
	{
		envPtr = *environCursor;
		namePtr = pathName;
		while (*envPtr == *namePtr)
		{
			if (*envPtr == '=')
				break;
			envPtr++;
			namePtr++;
		}
		if ((*envPtr == '=') && (*namePtr == '\0'))
			return (envPtr + 1);
		environCursor++;
	}
	return (NULL);
}
