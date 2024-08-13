#include "shell.h"

/**
 * prompt - prints '$' and waits for user input
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
