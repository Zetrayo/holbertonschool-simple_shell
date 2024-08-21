#include "shell.h"

/**
 * execute_command - Executes a command or launches an appropriate executable
 * @command: Full command line input
 * @prog_name: Name of the program
 * Description: Takes a full command line input, tokenizes it to form arguments
 * and if the command is not a built-in command, it forks a child process and
 * executes the command using execve.
 * Return: Returns 127 when command not found, 0 otherwise
 */
int execute_command(char *command, char *prog_name)
{
	pid_t pid;
	int status, command_check;
	char full_path[BUFSIZE], *argv[BUFSIZE];

	command_check = prepare_command(command, full_path, argv);
	if (command_check == -1)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, argv[0]);
		exit(127);
	}
	else if (command_check == 1)
	{
		return (0);
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
	return (0);
}

/**
 * prepare_command - Prepares the command and its arguments
 * @command: Command string to process
 * @full_path: Buffer to store the full path of the command
 * @argv: Array to store the command and its arguments
 * Return: 0 on success, -1 if the command is not found
 */
int prepare_command(char *command, char *full_path, char **argv)
{
	int argc = 0;
	char *token, *path;

	if (check_builtin_commands(command))
	{
		return (1);
	}
	while (*command == ' ' || *command == '\t')
		command++;

	if (*command == '\0')
		return (1);
	token = strtok(command, " ");
	while (token != NULL && argc < BUFSIZE - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	if (argc == 0)
		return (-1);

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
 * Description: copies a certain number of chars
 * from one string to another
 * @str: pointer pointing to string
 * @str_two: pointer pointing to string
 * @n: number of characters to copy
 * Return: 0 (Success)
 */
char *_strncpy(char *str, char *str_two, int n)
{
	int index = 0;

	for (index = 0; index < n && str_two[index] != '\0'; index++)
	{
		str[index] = str_two[index];
	}
	for (; index < n; index++)
	{
		str[index] = '\0';
	}
	return (str);
}
