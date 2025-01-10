#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

#define BUFFER_SIZE 1024

int exit_command(const char *input);
char *read_input(void);
void execute(char *input);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strtok(char *str, const char *tok);
char *_strdup(char *str);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
unsigned int check_delim(char c, const char *str);
char *find_command_path(char *command);

#endif
