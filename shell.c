#include "main.h"
/**
  * main_helper - helper function for main
  * @fcommand: tokenaized user command
  * @status: status about echo
  * @buf: user input
  * Return: if break needed 1 else 0
  */
int main_helper(char **fcommand, int status, char *buf, char **argv)
{
	if (fcommand == NULL)
	{
		free(buf);
		free_path();
		if (status)
			printf("\n");
		return (1);
	}
	else if (!custom_strcmp(fcommand[0], "exit"))
	{
		if (fcommand[1] != NULL)
		{
			long exit_status;
			char *endptr;
			exit_status = custom_strtol(fcommand[1], &endptr, 10);
			if (*endptr != '\0' || exit_status < 0)
			{
				fprintf(stderr, "%s: Illegal number: %s\n", argv[0], fcommand[1]);
				exit(EXIT_FAILURE);
			}
			free(buf);
			free_path();
			free(fcommand);
			exit(exit_status);
		}
		else
		{
			free(buf);
			free_path();
			free(fcommand);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

/**
  * main - shell start function
  * @argv: argument variables
  * @argc: argument count
  * @env: env variables
  * Return: always 0
  */
int main(int argc, char **argv, char **env)
{
	char **fcommand, *buf, *command;
	int status, lk = 0, r_code = 0;

	(void)argc, path_var = get_path(env);
	while (1)
	{
		status = isatty(STDIN_FILENO), print_prompt(status);
		fcommand = get_command(&buf);
		if (main_helper(fcommand, status, buf, argv))
			break;
		if (!custom_strcmp(fcommand[0], " "))
		{
			free(buf), free(fcommand[0]), free(fcommand);
			continue;
		}
		command = custom_strdup(fcommand[0]);
		if (!custom_strcmp("env", fcommand[0]))
		{
			print_env(), free(buf), free(fcommand), free(command);
			continue;
		}
		fcommand[0] = find_file(fcommand[0], &lk);
		if (!fcommand[0])
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], command);
			free(buf), free(fcommand), free(command), errno = 0;
			if (!status)
				free_path(), exit(127);
			continue;
		}
		r_code = exec_c(fcommand), free(buf);
		if (lk)
			free(fcommand[0]), lk = 0;
		free(fcommand), free(command);
	}
	return (r_code);
}
