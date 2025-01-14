#include "shell.h"

static char *read_input(void);
static int process_input(char *input, char *program_name);
static void cleanup(char *input, char **args);

/**
 * main - Entry point for the shell
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	char *input;
	int status = EXIT_SUCCESS;
	char *program_name = (argc > 0) ? argv[0] : "hsh";

	while (1)
	{
		input = read_input();
		if (input == NULL)
			break;

		status = process_input(input, program_name);
		free(input);

		if (status == EXIT_FAILURE)
			break;
	}

	return (status);
}

/**
 * read_input - Read input from the user
 * Return: The input string or NULL on EOF or error
 */
static char *read_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t input_count;
	/*Display prompt if running in interactive mode*/
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	input_count = getline(&input, &input_size, stdin);
	/*Handle EOF or error*/
	if (input_count == -1)
	{
		free(input);
		return (NULL);
	}
	/*Remove trailing newline if present*/
	if (input_count > 0 && input[input_count - 1] == '\n')
		input[input_count - 1] = '\0';

	return (input);
}

/**
 * process_input - Process the user input
 * @input: The user input string
 * @program_name: Name of the shell program
 * Return: EXIT_SUCCESS to continue, EXIT_FAILURE to exit
 */
static int process_input(char *input, char *program_name)
{
	char **args;
	int status = EXIT_SUCCESS;
	/*Check for exit command*/
	if (strcmp(input, "exit") == 0)
		return (EXIT_FAILURE);
	/*Check for env command*/
	if (strcmp(input, "env") == 0)
	{
		print_environment();
		return (EXIT_SUCCESS);
	}
	/*Split input into arguments*/
	args = split_line(input);
	if (args == NULL)
		return (EXIT_SUCCESS);
	/*Execute the command if args[0] is not NULL*/
	if (args[0] != NULL)
		status = execute_command(args, program_name);

	cleanup(NULL, args);
	return ((status == 127) ? EXIT_SUCCESS : status);
}
/**
 * cleanup - Clean up resources
 * @input: The input string to free
 * @args: The argument array to free
 */
static void cleanup(char *input, char **args)
{
	if (input != NULL)
		free(input);
	if (args != NULL)
		free(args);
}
/**
 * print_environment - print the env
 */
void print_environment(void)
{
	char **env = environ;
	/*Iterate through environment variables and print each one*/
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
