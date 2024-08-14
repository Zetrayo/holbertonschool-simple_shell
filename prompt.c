#include "shell.h"

/**
 * main - prints '$' and waits for user input
 * Return: 0 always
 */
int main(void)
{
	int i = 0, b;
	char c[30];

	printf("$ ");
	while ((c[i] = getchar()) != '\n' && i < 30 - 1)
	{
		i++;
	}
	c[i] = '\0';
	b = i;
	i = 0;
	while (i < b)
	{
		printf("%c", c[i]);
		i++;
	}
	printf("\n");
	return (0);
}
