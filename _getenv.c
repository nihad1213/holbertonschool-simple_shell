#include "shell.h"
char _getenv(const char *name)
{
	int i, j, flag;
	char *current_env = NULL;

	for (i = 0; environ[i] != NULL; i++)
	{
		flag = 0;
		current_env = environ[i];
		for (j = 0; current_env[j] != '='; j++)
		{
			if (name[j] != current_env[j])
				flag = 1;
		}
		if (flag == 0)
			return (environ[i]);
	}
	return (NULL);
}
