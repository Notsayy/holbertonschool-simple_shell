#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * main - Entry point for the mini shell
 *
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t input_length;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		input_length = getline(&input, &input_size, stdin);

		if (input_length == -1)
		{
			free(input);
			input = NULL;
			break;
		}

		if (input_length > 0 && input[input_length - 1] == '\n')
			input[input_length - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			input = NULL;
			break;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(input);
			exit(1);
		}

		if (pid == 0)
		{
			char *args[2];
			args[0] = input;
			args[1] = NULL;
			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(1);
			}

		}
		else
		{
			wait(NULL);
		}
    }

	return (0);
}
