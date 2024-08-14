#include "shell.h"

/**
 * main - Executes the command 'ls -l /tmp' in 5 different child processes
 * Each child is created by the same parent process.the parent waits for a
 * child to exit before creating a new child.
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int i;

	for (i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			printf("Wait for me, wait for me\n");
			sleep(3);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
