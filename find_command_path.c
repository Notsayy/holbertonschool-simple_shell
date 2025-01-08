#include "shell.h"

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
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}

	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path_len = strlen(dir) + strlen(command) + 2;

		full_path = malloc(full_path_len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		full_path[0] = '\0';
		strcat(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
