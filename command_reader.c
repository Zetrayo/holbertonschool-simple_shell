#include "shell.h"

/**
 * _strcmp - Entry point
 * Description: 'compares string to another string'
 *
 * @a: pointer pointing to string
 * @b: pointer pointing to string
 * Return: 0 (Success)
 */
int _strcmp(char *a, char *b)
{
	int c = 0;

	while (*a == *b)
	{
		if (*a == '\0' && *b == '\0')
		{
			return (0);
		}
		a++;
		b++;
	}
	c = (*a - *b);
	return (c);
}

/**
 * read_command - Reads a command from standard input
 * Return: dynamically allocated string with the command, or NULL on failure
 */
char *read_command(void)
{
	char *buffer, *new_buffer;
	int bytes_read, i = 0, j, bufsize = BUFSIZE;

	buffer = (char *)malloc(bufsize);
	if (buffer == NULL)
	{
		free(buffer);
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
		if (i >= bufsize - 1)
		{
			bufsize += 1;
			new_buffer = (char *)malloc(bufsize);
			if (new_buffer == NULL)
			{
				fprintf(stderr, "allocation error\n");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			for (j = 0; j < i; j++)
				new_buffer[j] = buffer[j];
			free(buffer);
			buffer = new_buffer;
		}
	}
	return (buffer);
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

	if (_strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
		return (1);
	}
	else if (_strcmp(cmd, "env") == 0)
	{
		while (*env)
		{
			printf("%s\n", *env++);
		}
		return (1);
	}
	return (0);
}
