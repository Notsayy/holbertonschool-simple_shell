#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * execute - Execute the the command
 * @input: User input command
 *
 */


void execute(char *input)
{
	char *args[2];
	char *path = find_command_path(input);

	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", input);
		exit(127);
	}

	args[0] = path;
	args[1] = NULL;

	if (execve(path, args, NULL) == -1)
	{
		perror("execve");
		free(path);
		exit(1);
	}

	free(path);
}

