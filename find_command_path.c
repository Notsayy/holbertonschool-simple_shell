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

	for (i = 0; environ[i]; i++)/*Iterate through environment variables to find the PATH variable*/
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)/*Check if the variable is "PATH"*/
		{
			path_env = environ[i] + 5;/*Skip "PATH=" to get the actual value*/
			break;
		}
	}
	/*If PATH is not found in the environment variables, return NULL*/
	if (!path_env)
		return (NULL);
	/*Create a copy of the PATH string to tokenize it safely*/
	path_copy = strdup(path_env);
	if (!path_copy)/*Check for memory allocation failure*/
		return (NULL);
	/*Tokenize the PATH string to get each directory*/
	dir = strtok(path_copy, ":");
	while (dir)
	{
		/*Calculate the length needed for the full path*/
		full_path_len = strlen(dir) + strlen(command) + 2;
		/*Allocate memory for the full path*/
		full_path = malloc(full_path_len);
		if (!full_path)/* Handle memory allocation failure*/
		{
			free(path_copy);
			return (NULL);
		}
		/*Build the full path by concatenating directory, "/", and command*/
		full_path[0] = '\0';
		strcat(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)/*Check if the command exists and is executable in this directory*/
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
