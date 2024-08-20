#include "shell.h"

/**
 * _strcmp - Compares string a to string b
 * @a: pointer pointing to string a
 * @b: pointer pointing to string b
 * Return: 0 if strings are equal, non-zero otherwise
 */
int _strcmp(char *a, char *b)
{
	while (*a == *b)
	{
		if (*a == '\0')
			return (0);
		a++;
		b++;
	}
	return (*a - *b);
}

/**
 * reallocate_buffer - Reallocates memory for a buffer
 * @buffer: pointer to the original buffer
 * @bufsize: current size of the buffer
 * @i: current index of the buffer
 * Return: pointer to the reallocated buffer, or NULL on failure
 */
char *reallocate_buffer(char *buffer, int bufsize, int i)
{
	char *new_buffer;
	int j;

	new_buffer = (char *)malloc(bufsize + 1);
	if (new_buffer == NULL)
	{
		fprintf(stderr, "allocation error\n");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	for (j = 0; j < i; j++)
		new_buffer[j] = buffer[j];
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
 * @cmd: Command to check
 * Return: 1 if command is built-in, 0 otherwise
 */
int check_builtin_commands(char *cmd)
{
	if (_strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(cmd, "env") == 0)
	{
		char **env = environ;

		while (*env)
			printf("%s\n", *env++);
		return (1);
	}
	return (0);
}
