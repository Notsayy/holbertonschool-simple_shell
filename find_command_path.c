#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "shell.h"

#define PATH_MAX 1024

/**
 * find_command_path - find the path of a command
 * @command: command searched
 *
 * Return: Full path of the command if found, otherwise NULL
 */

char *find_command_path(char *command)
{
char *path_copy, *dir, *full_path, *path_env = NULL;
size_t full_path_len;
int i;

for (i = 0; environ[i]; i++)
{
	if (_strncmp(environ[i], "PATH=", 5) == 0)
	{
		path_env = environ[i] + 5;
		break;
	}
}
	if (!path_env)
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = _strtok(path_copy, ":");
	while (dir)
	{
		full_path_len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(full_path_len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
