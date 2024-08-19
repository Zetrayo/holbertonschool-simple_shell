#include "shell.h"

/**
 * prompt - displays a prompt for the user
 */
void prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * read_command - reads a command from standard input
 * Return: dynamically allocated string with the command, or NULL on failure
 */
char *read_command(void)
{
	char *buffer = malloc(BUFSIZE);
	int bytes_read;
	int i = 0;

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
 * _getenv - gets the value of the global variable
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
