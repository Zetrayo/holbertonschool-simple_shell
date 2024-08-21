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
int execute_command(char *command, char *prog_name);
int check_builtin_commands(char *command);
char *_getenv(const char *name);
int find_path(char *result_path, size_t size, char *command, char *path);
int _strlen(char *str);
int _strcmp(char *str, char *str_two);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *str, char *str_two, int n);
int prepare_command(char *command, char *full_path, char **argv);

extern char **environ;

#endif
