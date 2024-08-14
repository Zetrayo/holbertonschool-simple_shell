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
	size_t length;  /** Déclaration au début du bloc */

	if (!buffer)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	if (fgets(buffer, BUFSIZE, stdin) == NULL)
	{
		free(buffer);
		return (NULL);  /** Gestion de EOF ou d'erreur de lecture */
	}
	/** Trim the newline character from the buffer if present */
	length = strlen(buffer);
	if (length > 0 && buffer[length - 1] == '\n')
	{
		buffer[length - 1] = '\0';
	}
	return (buffer);
}
