#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * handle_input - reads and processes user input
 * @input: Pointer to the input
 * @input_size: Pointer to the size of the input
 *
 * Return: length of the input, or -1
 */

ssize_t handle_input(char **input, size_t *input_size)
{
	printf("$ ");
	fflush(stdout);
	return getline(input, input_size, stdin);
}

/**
 * process_command - forks a child process to execute a command
 * @input: user command input
 */

void process_command(char *input)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execute(input);
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - entry point for the mini shell
 *
 * Return: 0
 */

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t input_length;

	while (1)
	{
		input_length = handle_input(&input, &input_size);

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
		process_command(input);

	}
	free(input);
	return (0);
}
