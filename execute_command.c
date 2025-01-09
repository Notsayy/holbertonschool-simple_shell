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

	command_path = find_command_path(args[0]);/*Get the full path of the command*/
	if (args[0][0] != '/' && args[0][0] != '.' && command_path == NULL)
	{
		print_error(program_name, args[0]);
		return;
	}
	pid = fork(); /*Create a new child process*/
	if (pid == 0)
	{
		if (command_path != NULL) /*If the command was found in PATH, execute it*/
		{
			if (execve(command_path, args, environ) == -1) /*Execute the command*/
			{
				print_error(program_name, args[0]); /*Error handling if execve fails*/
				exit(EXIT_FAILURE);
			}
		}
		else /*If the command was not in PATH but is a direct path*/
		{
			if (execve(args[0], args, environ) == -1)/*Execute the direct path command*/
			{
				print_error(program_name, args[0]); /*Error handling if execve fails*/
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (pid < 0) /*Error handling for fork failure*/
	{
		fprintf(stderr, "%s: Error: Unable to create child process\n", program_name);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED); /*Wait for the child process to complete*/
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
