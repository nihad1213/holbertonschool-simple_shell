#include "main.h"

/**
 * execute - executes command
 *
 *@command: The command string to execute.
 *
 * Return: the exit status of the executed command,
 * or -1 if an error occurs.
 */
int execute(char *command)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        free(command);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execute_child(command);
    }
    else
    {
        status = execute_parent(pid);
    }

    free(command);
    return status;
}

/**
 * execute_child - executes command in child process
 *
 * @command: The command string to execute.
 */
void execute_child(char *command)
{
    char *arr[64];
    line_div(command, arr);

    if (arr[0] == NULL)
    {
        exit(EXIT_SUCCESS);
    }

    if (strcmp(arr[0], "env") == 0)
    {
        print_environment();
    }

    if (strchr(arr[0], '/') != NULL)
    {
        execute_absolute_path(arr);
    }
    else
    {
        execute_relative_path(arr);
    }
}

/**
 * execute_parent - waits for child process to finish and returns status
 *
 * @pid: The process ID of the child process.
 * 
 * Return: the exit status of the child process.
 */
int execute_parent(pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    else
    {
        return 1;
    }
}

/**
 * print_environment - prints environment variables
 */
void print_environment()
{
    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }

    exit(EXIT_SUCCESS);
}

/**
 * execute_absolute_path - executes command with absolute path
 *
 * @arr: Array of strings containing command and arguments.
 */
void execute_absolute_path(char *arr[])
{
    if (access(arr[0], X_OK) == 0)
    {
        if (execve(arr[0], arr, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    fprintf(stderr, "./hsh: 1: %s: not found\n", arr[0]);
    exit(127);
}

/**
 * execute_relative_path - executes command with relative path
 *
 * @arr: Array of strings containing command and arguments.
 */
void execute_relative_path(char *arr[])
{
    char *path = getenv("PATH");
    char *token;

    if (path == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", arr[0]);
        exit(127);
    }

    token = strtok(path, ":");
    while (token != NULL)
    {
        char executable_path[256];
        snprintf(executable_path, sizeof(executable_path), "%s/%s", token, arr[0]);
        if (access(executable_path, X_OK) == 0)
        {
            if (execve(executable_path, arr, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, ":");
    }

    fprintf(stderr, "./hsh: 1: %s: not found\n", arr[0]);
    exit(127);
}

