#include <errno.h>
#include "main.h"

#define BUFFER_SIZE 10000

/**
 * custom_getline - Custom getline function
 * Return: Returns string from buffer
 */
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 0;
	static int bytes_read = 0;
	char *line = NULL;
	int line_size = 0;
	int i;

	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			pos = 0;
			if (bytes_read <= 0)
				return (NULL);
		}

		while (pos < bytes_read)
		{
			if (buffer[pos] == '\n')
			{
				line = (char *)malloc(line_size + 1);
				if (line == NULL)
					return (NULL);

				for (i = 0; i < line_size; i++)
					line[i] = buffer[pos - line_size + i];
				line[i] = '\0';
				pos++;
				return (line);
			}
			line_size++;
			pos++;
		}
	}
}

/**
 * arg_counter - counts number of arguments
 * @buf: user input
 * @size: size of user input
 * Return: number of arguments
 */
int arg_counter(char *buf, int size)
{
    int count = 0, i;

    if (buf == NULL || size <= 0)
    {
        return (0);
    }

    for (i = 0; i < size; i++)
    {
        if ((i == 0 && buf[i] != ' ') || (i > 0 && buf[i - 1] == ' ' && buf[i] != ' ' && buf[i] != '\n'))
            count++;
    }

    if (size > 0 && buf[size - 1] != '\n')
    {
        count++;
    }

    return (count);
}



/**
 * get_command - format command line arguments
 * @buf: buffer for storing user input
 * Return: memory address where arguments are stored
 */
char **get_command(char **buf)
{
	char **array;
	size_t k, i, l = 0, count;

	*buf = custom_getline();
	if (*buf == NULL)
	{
		return (NULL);
	}

	k = 0;
	while ((*buf)[k] != '\0' && (*buf)[k] != '\n')
	{
		k++;
	}

	count = arg_counter(*buf, k);
	if (!count)
	{
		array = malloc(sizeof(char *));
		if (array == NULL)
		{
			free(*buf);
			return NULL;
		}
		array[0] = malloc(sizeof(char));
		if (array[0] == NULL)
		{
			free(*buf);
			free(array);
			return NULL;
		}
		array[0][0] = '\0';
		return (array);
	}

	array = malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
	{
		free(*buf);
		return (NULL);
	}
	
	for (i = 0; i < k; i++)
	{
		if ((*buf)[i] == ' ' || (*buf)[i] == '\t' || (*buf)[i] == '\n')
			(*buf)[i] = '\0';
		else if (i == 0 || (*buf)[i - 1] == '\0')
		{
			array[l] = *buf + i;
			l++;
		}
	}
	array[l] = NULL;
	return (array);
}
