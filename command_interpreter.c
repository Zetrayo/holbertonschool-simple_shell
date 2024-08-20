#include "shell.h"

/**
 * execute_command - Executes a command or launches an appropriate executable
 * @cmd: Full command line input
 * @prog_name: Name of the program
 * Description: Takes a full command line input, tokenizes it to form arguments
 * and if the command is not a built-in command, it forks a child process and
 * executes the command using execve.
 */
void execute_command(char *cmd, char *prog_name)
{
	pid_t pid;
	int status, mem;
	char full_path[BUFSIZE], *argv[BUFSIZE];

	mem = prepare_command(cmd, full_path, argv);
	if (mem == -1)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, argv[0]);
		exit(127);		/* Return status code 127 for order not found */
	}
	else if (mem == 1)
	{
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror("prog_name");
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
 * prepare_command - Prepares the command and its arguments
 * @cmd: Command string to process
 * @full_path: Buffer to store the full path of the command
 * @argv: Array to store the command and its arguments
 * Return: 0 on success, -1 if the command is not found
 */
int prepare_command(char *cmd, char *full_path, char **argv)
{
	int argc = 0;
	char *token, *path;

	while (*cmd == ' ' || *cmd == '\t')
		cmd++;

	if (*cmd == '\0')
		return (1);
	token = strtok(cmd, " ");
	while (token != NULL && argc < BUFSIZE - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	if (argc == 0)
		return (-1);

	if (check_builtin_commands(argv[0]) == 1)
		return (1);

	if (argv[0][0] == '/' || argv[0][0] == '.' || strncmp(argv[0], "../", 3) == 0)
	{
		_strncpy(full_path, argv[0], BUFSIZE - 1);
		full_path[BUFSIZE - 1] = '\0';
	}
	else
	{
		path = _getenv("PATH");
		if (find_path(full_path, BUFSIZE, argv[0], path) != 0)
		{
			return (-1);
		}
	}
	return (0);
}

/**
 * _strncpy - Entry point
 * Description: 'prints a determined number of array elements'
 *
 * @a: pointer pointing to string
 * @b: pointer pointing to string
 * @n: number of characters to copy
 * Return: 0 (Success)
 */
char *_strncpy(char *a, char *b, int n)
{
	int i = 0;

	for (i = 0; i < n && b[i] != '\0'; i++)
	{
		a[i] = b[i];
	}
	for (; i < n; i++)
	{
		a[i] = '\0';
	}
	return (a);
}
