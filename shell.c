#include "shell.h"
/**
 * execute_command - Executes a command or launches an appropriate executable
 * @cmd: Full command line input
 *
 * Description: Takes a full command line input, tokenizes it to form arguments
 * and if the command is not a built-in command, it forks a child process and
 * executes the command using execvp.
 */
void execute_command(char *cmd)
{
	char *argv[100];				/** Array to hold command arguments */
	int argc = 0, status;				/** Argument count */
	char *token = strtok(cmd, " ");
	pid_t pid;	/** Tokenize the command */

	while (token != NULL)
	{
		argv[argc] = token;
		token = strtok(NULL, " ");
		argc++;
	}
	argv[argc] = NULL;				/** NULL-terminate the argument list */
	if (argc == 0)					/** No command entered */
		return;

	if (check_builtin_commands(argv[0]))/** Check for built-in commands */
	{
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("fork");/** Fork failed */

	else
	{
		waitpid(pid, &status, 0);/** Parent process */
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
