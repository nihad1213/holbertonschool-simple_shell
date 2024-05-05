#include "shell.h"
/**
  * _getenv - gets the environment value from a key
  * @name: string to search through environments for
  * Return: value of the key as a string
  */
char *_getenv(const char *name)
{
	int i, j, len;
	char **env, *tmp;

	if (!name)
		return (NULL);
	env = environ;
	for (i = 0; env[i]; i++)
	{
		for (len = 0; env[i][len] != '='; len++)
			;
		len++;
		tmp = malloc((len) * sizeof(char));
		_memcpy(tmp, env[i], len - 1);
		tmp[len - 1] = '\0';
		if (_strncmp((char *)name, tmp, _strlen(tmp)) == 0)
		{
			free(tmp);
			tmp = NULL;
			for (j = 0; env[i][j]; j++)
			{
				if (env[i][j] == '=')
				{
					tmp = &env[i][j + 1];
					break;
				}
			}
			return (tmp);
		}
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}
