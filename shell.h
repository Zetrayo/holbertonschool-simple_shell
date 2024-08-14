#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Define a buffer size for command input */
#define BUFSIZE 1024


/* Function Prototypes */

void prompt(void);                      // Prints the shell prompt
char *read_command(void);               // Reads a command from the user input
void execute_command(char *cmd);        // Executes the given command
int check_builtin_commands(char *cmd);  // Checks and executes built-in commands
void free_resources(char *cmd, char **args);  // Frees allocated resources

extern char **environ;

#endif
