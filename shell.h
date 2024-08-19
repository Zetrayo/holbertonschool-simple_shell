#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* Define a buffer size for command input */
#define BUFSIZE 1024

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;

/* Function Prototypes */
void prompt(void);
char *read_command(void);
void execute_command(char *cmd);
int check_builtin_commands(char *cmd);
char *_getenv(const char *name);
int find_path(char *result_path, size_t size, char *command, char *path);

extern char **environ;

#endif
