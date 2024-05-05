#include "shell.h"
/**
 * _getenv - gets the path
 * @path_name: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 */
char *_getenv(const char *name) 
{
    extern char **environ; // Declaring environ as an external variable
    char **env = environ;

    size_t namelen = strlen(name);

    while (*env != NULL) 
    {
        if (strncmp(*env, name, namelen) == 0 && (*env)[namelen] == '=') 
	{
            // Found the environment variable, return its value
            return *env + namelen + 1;
        }
        env++;
    }

    // Environment variable not found
    return NULL;
}
