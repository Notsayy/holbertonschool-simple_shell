#include "shell.h"

/**
 * main - Entry point for the mini shell
 *
 * Return: 0
 */
int main(void)
{
	char *input;
	size_t input_size = 0;
	ssize_t input_length;

	while (1)
	{
		printf("$ ");
		input_length = getline(&input, &input_size, stdin);

		if (input_length == -1)
		{
			free(input);
			break;
		}

		if (input_length > 0 && input[input_length - 1] == '\n')
			input[input_length - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
	}

	return (0);
}
