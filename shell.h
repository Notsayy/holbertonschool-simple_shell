#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
extern char **environ;
#define BUFFER_SIZE 1024
char **split_line(char *line);
int execute_command(char **args, char *program_name);
void print_error(char *program_name, char *command);
char *find_command_path(char *command);
void print_environment(void);

#endif
