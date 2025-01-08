#include "shell.h"

/**
 * execute_command - forks a new process and executes the command
 * @args: the command to be executed
 * @program_name: Name of the shell program
 * Return: void
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command_path(args[0]);
	if (args[0][0] != '/' && args[0][0] != '.' && command_path == NULL)
	{
		print_error(program_name, args[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (command_path != NULL)
		{
			if (execve(command_path, args, environ) == -1)
			{
				print_error(program_name, args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execve(args[0], args, environ) == -1)
			{
				print_error(program_name, args[0]);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (pid < 0)
	{
		fprintf(stderr, "%s: Error: Unable to create child process\n", program_name);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * print_error - Prints an error message when a command is not found
 * @program_name: Name of the shell program
 * @command: the command to be executed
 * Return: void
 */
void print_error(char *program_name, char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
}
