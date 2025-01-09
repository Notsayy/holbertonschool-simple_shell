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

	for (i = 0; environ[i]; i++)/*Find the PATH variable*/
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)/*Check if the variable is "PATH"*/
		{
			path_env = environ[i] + 5;/*Skip "PATH=" to get the actual value*/
			break;
		}
	}
	if (!path_env)/*If PATH is not found,return NULL*/
		return (NULL);
	path_copy = strdup(path_env);/*Copy the PATH string to tokenize it*/
	if (!path_copy)/*Check for memory allocation failure*/
		return (NULL);
	dir = strtok(path_copy, ":");/*Tokenize thePATH string to get each directory*/
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)/* Handle memory allocation failure*/
		{
			free(path_copy);
			return (NULL);
		}
		full_path[0] = '\0';/*Build the full path by concatenating directory*/
		strcat(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0)/*Check if the command exists*/
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");/*Get the next directory in PATH*/
	}
	free(path_copy);
	return (NULL);
}
