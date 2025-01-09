#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: argc
 * @argv: argv
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t input_count;
	char *program_name = argv[0];
	char **args;
	int status = EXIT_SUCCESS;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

		input_count = getline(&input, &input_size, stdin); /* Read the user input */

		if (input_count == -1)
		{
			free(input);
			break; /* Exit on EOF */
		}

		if (input_count > 0 && input[input_count - 1] == '\n')
			input[input_count - 1] = '\0'; /* Remove newline */

		if (strcmp(input, "exit") == 0) /* Handle 'exit' command */
		{
			free(input);
			return (EXIT_SUCCESS);
		}

		args = split_line(input);
		if (args == NULL) /* Handle memory allocation failure */
			continue;

		if (args[0] != NULL)
		{
			status = execute_command(args, program_name);
		}

		free(args);
		if (status != EXIT_SUCCESS)
        {
            free(input);
            return status;
        }
    }
    return (status);
}
