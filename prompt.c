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
	int bytes_read;				/* Nombre de bytes lus par read */

	if (!buffer)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	/* Utilisation de read pour lire depuis stdin */
	bytes_read = read(STDIN_FILENO, buffer, BUFSIZE - 1);

	if (bytes_read < 0)
	{	/* Gestion des erreurs de read */
		perror("read");
		free(buffer);
		return (NULL);
	}

	if (bytes_read == 0)
	{	/* EOF ou aucun caractère lu */
		free(buffer);
		return (NULL);
	}

	/* Assurer que la chaîne est terminée par un caractère nul */
	buffer[bytes_read] = '\0';

	/* Trim the newline character from the buffer if present */
	if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
	{
		buffer[bytes_read - 1] = '\0';
	}

	return (buffer);
}
