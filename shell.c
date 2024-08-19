#include "shell.h"

/**
 * execute_command - Executes a command or launches an appropriate executable
 * @cmd: Full command line input
 *
 * Description: Takes a full command line input, tokenizes it to form arguments
 * and if the command is not a built-in command, it forks a child process and
 * executes the command using execve.
 */
void execute_command(char *cmd)
{
    char *argv[BUFSIZE];                /* Array to hold command arguments */
    int argc = 0, status;           /* Argument count */
    char *token = strtok(cmd, " ");
    pid_t pid;                      /* Tokenize the command */
    char *path = _getenv("PATH");   /* Get the PATH environment variable */
    char full_path[BUFSIZE];           /* Buffer to hold the full path of the command */

    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;              /* NULL-terminate the argument list */

    if (argc == 0)                  /* No command entered */
        return;

    if (check_builtin_commands(argv[0])) /* Check for built-in commands */
        return;

    /* Find the executable in the PATH */
    if (find_executable_path(full_path, sizeof(full_path), argv[0], path) != 0)
    {
        fprintf(stderr, "Command not found: %s\n", argv[0]);
        return;
    }

    pid = fork();
    if (pid == 0) /* Child process */
    {
        if (execve(full_path, argv, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork"); /* Fork failed */
    }
    else
    {
        waitpid(pid, &status, 0); /* Parent process waits for the child */
    }
}

/**
 * check_builtin_commands - Check and execute built-in commands
 * @cmd: Command to check
 * Return: 1 if command is built-in, 0 otherwise
 *
 * Description: Checks if the command is a built-in command such as 'exit'
 * or 'env'. If it is, the command is executed directly by the shell.
 */
int check_builtin_commands(char *cmd)
{
	char **env = environ;

	if (strcmp(cmd, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		return (1);
	}
	else if (strcmp(cmd, "env") == 0)
	{
		while (*env)
		{
			printf("%s\n", *env++);
		}
		return (1);
	}
	return (0);
}

/**
 * find_executable_path - Resolves the full path of an executable from PATH
 * @result_path: Buffer to store the resolved path
 * @size: Size of the buffer
 * @command: Command to find
 * @path: PATH environment variable
 * Return: 0 if found, -1 if not found
 */
int find_executable_path(char *result_path, size_t size, char *command, char *path)
{
	char *path_copy;
	char *token;
	char current_path[BUFSIZE];

	if (command == NULL || path == NULL || result_path == NULL)
		return (-1);

	/* Make a copy of the PATH environment variable */
	path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL)
		return (-1);
	strcpy(path_copy, path);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		sprintf(current_path, "%s/%s", token, command);
		if (access(current_path, X_OK) == 0)
		{
			memcpy(result_path, current_path, size);
			free(path_copy);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (-1);
}
/**
 * main - Entry point for a simple shell implementation
 * Return: Always 0
 *
 * Description: Runs a continuous loop that displays a prompt, reads a
 * command, and executes it. It will only terminate when an 'exit' command
 * is executed or an error occurs.
 */
int main(void)
{
	char *cmd = NULL;

	while (1)
	{
		prompt();
		cmd = read_command();
		if (cmd == NULL)
		{
			free(cmd);
			return (0);
		}

		execute_command(cmd);
		free(cmd);
	}
	return (0);
}
