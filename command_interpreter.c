#include "shell.h"

/**
 * read_command - Reads a command from standard input
 * Return: dynamically allocated string with the command, or NULL on failure
 */
char *read_command(void)
{
	char *buffer = malloc(BUFSIZE);
	int bytes_read, i = 0;

	if (buffer == NULL)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		bytes_read = read(STDIN_FILENO, buffer + i, 1);
		if (bytes_read <= 0)
		{
			free(buffer);
			return (NULL);
		}
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break;
		}
		i++;
		if (i >= BUFSIZE - 1)
		{
			buffer = realloc(buffer, BUFSIZE + BUFSIZE);
			if (buffer == NULL)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (buffer);
}

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
	pid_t pid;
	int argc = 0, status;
	char *token = strtok(cmd, " "), full_path[BUFSIZE];
	char *argv[BUFSIZE], *path = _getenv("PATH");

	while (token != NULL)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	if (argc == 0)
		return;

	if (check_builtin_commands(argv[0]))
		return;

	if (find_path(full_path, sizeof(full_path), argv[0], path) != 0)
	{
		fprintf(stderr, "Command not found: %s\n", argv[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * _getenv - Gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}

/**
 * check_builtin_commands - Check and execute built-in commands
 * @cmd: Command to check
 * Return: 1 if command is built-in, 0 otherwise
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
