#include "shell.h"

/**
 * _ppid - PID
 *
 * Return: Always 0.
 */
int _ppid(void)
{
	pid_t parent_pid;

	parent_pid = getppid();
	printf("%u\n", parent_pid);
	return (0);
}
