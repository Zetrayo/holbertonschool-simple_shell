#include "shell.h"

/**
 * find_path - Resolves the full path of an executable from PATH
 * @result_path: Buffer to store the resolved path
 * @size: Size of the buffer
 * @command: Command to find
 * @path: PATH environment variable
 * Return: 0 if found, -1 if not found
 */
int find_path(char *result_path, size_t size, char *command, char *path)
{
	char *path_copy;
	char *token;
	char current_path[BUFSIZE];
	size_t j;

	if (command == NULL || path == NULL || result_path == NULL)
		return (-1);

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
			for (j = 0; j < size; j++)
			{
				result_path[j] = current_path[j];
			}
			free(path_copy);
			return (0);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (-1);
}

/**
 * prompt - Displays a prompt for the user
 */
void prompt(void)
{
	printf("$ ");
	fflush(stdout);
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
