#include "shell.h"

/**
 * _strcmp - Compares two strings
 * @str: pointer pointing to string
 * @str_two: pointer pointing to string
 * Return: 0 if strings are equal,
 * difference in lenght otherwise
 */
int _strcmp(char *str, char *str_two)
{
	while (*str == *str_two)
	{
		if (*str == '\0')
			return (0);
		str++;
		str_two++;
	}
	return (*str - *str_two);
}

/**
 * reallocate_buffer - Reallocates memory for a buffer
 * @buffer: pointer to the original buffer
 * @bufsize: current size of the buffer
 * @index: current current_index of the buffer
 * Return: pointer to the reallocated buffer, or NULL on failure
 */
char *reallocate_buffer(char *buffer, int bufsize, int index)
{
	char *new_buffer;
	int current_index;

	new_buffer = (char *)malloc(bufsize + 1);
	if (new_buffer == NULL)
	{
		fprintf(stderr, "allocation error\n");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	for (current_index = 0; current_index < index; current_index++)
		new_buffer[current_index] = buffer[current_index];
	free(buffer);
	return (new_buffer);
}

/**
 * read_command - Reads a command from standard input
 * Return: dynamically allocated string with the command, or NULL on failure
 */
char *read_command(void)
{
	char *buffer;
	int bytes_read, i = 0, bufsize = BUFSIZE;

	buffer = (char *)malloc(bufsize);
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
		if (i >= bufsize - 1)
		{
			bufsize *= 2;
			buffer = reallocate_buffer(buffer, bufsize, i);
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

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j] && name[j] == environ[i][j])
				j++;
			if (name[j] == '\0' && environ[i][j] == '=')
				return (environ[i] + j + 1);
		}
	}
	return (NULL);
}

/**
 * check_builtin_commands - Check and execute built-in commands
 * @command: Command to check
 * Return: 1 if command is built-in, 0 otherwise
 */
int check_builtin_commands(char *command)
{
	char **env = environ;

	if (_strcmp(command, "exit") == 0)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(command, "env") == 0)
	{
		while (*env)
			printf("%s\n", *env++);
		return (1);
	}
	return (0);
}
