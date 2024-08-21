#include "shell.h"

/**
 * _strlen - Entry point
 * Description: 'counts string lenght'
 * @str: pointer pointing to string
 * Return: lenght
 */
int _strlen(char *str)
{
	int lenght = 0;

	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return (lenght);
}

/**
 * _strcpy - Entry point
 * Description: 'copies a string into a new string'
 * @copy: pointer pointing to string
 * @str: pointer pointing to string
 * Return: new string copy
 */
char *_strcpy(char *copy, char *str)
{
	int index = 0;

	while (str[index] != '\0')
	{
		copy[index] = str[index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}

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
	size_t index;

	if (command == NULL || path == NULL || result_path == NULL)
		return (-1);

	path_copy = malloc(_strlen(path) + 1);
	if (path_copy == NULL)
		return (-1);

	_strcpy(path_copy, path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		sprintf(current_path, "%s/%s", token, command);
		if (access(current_path, X_OK) == 0)
		{
			for (index = 0; index < size; index++)
			{
				result_path[index] = current_path[index];
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
 * upon entering interactive mode
 */
void prompt(void)
{
	printf("($) ");
	fflush(stdout);
}

/**
 * main - Entry point for a simple shell implementation
 * Return: Always 0
 * @argc: Number of arguments
 * @prog_name: Name of the program
 * Description: Runs a continuous loop that displays a prompt, reads a
 * command, and executes it. It will only terminate when an 'exit' command
 * is executed or an error occurs.
 */
int main(int argc, char **prog_name)
{
	char *cmd = NULL;
	int interactive = isatty(STDIN_FILENO);

	if (argc < 0)
	{
		printf("Error");
		return (0);
	}
	while (1)
	{
		if (interactive)
		{
			prompt();
		}
		cmd = read_command();
		if (cmd == NULL)
		{
			free(cmd);
			return (0);
		}
		execute_command(cmd, prog_name[0]);
		free(cmd);
	}
	free(cmd);
	return (0);
}
