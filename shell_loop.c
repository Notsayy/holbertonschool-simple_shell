#include "shell.h"
/**
 * main - Entry point for the mini shell
 *
 * Return: void
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t input_count;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2); /*Display the shell prompt*/
		/*Read a line from standard input*/
		input_count = getline(&input, &input_size, stdin);

		if (input_count == -1)
		{
			break; /*Exit the loop if EOF*/
		}

		char **args = split_line(input);

		if (args[0] != NULL) /*check if there is a command entered*/
		{
			execute_command(args);
		}

		free(args);
	}

	free(input);
	return (EXIT_SUCCESS);
}
