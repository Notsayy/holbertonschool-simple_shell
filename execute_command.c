#include "shell.h"

/**
 * execute_child - Execute the command in the child process
 * @command_path: Full path of the command to execute
 * @args: Command arguments
 * @program_name: Name of the shell program
 *
 * Return: This function does not return if successful
 */
static void execute_child(char *command_path, char **args, char *program_name)
{
	if (execve(command_path, args, environ) == -1)
	{
		perror(program_name);
		if (command_path != args[0])
			free(command_path);
		exit(127);
	}
}

/**
 * handle_parent - Handle the parent process after forking
 * @pid: Process ID of the child
 * @program_name: Name of the shell program
 *
 * Return: The exit status of the child process
 */
static int handle_parent(pid_t pid, char *program_name)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror(program_name);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

/**
 * execute_command - Execute a command with given arguments
 * @args: Array of strings containing the command and its arguments
 * @program_name: Name of the shell program
 *
 * Return: The exit status of the executed command
 */
int execute_command(char **args, char *program_name)
{
	pid_t pid;
	char *command_path;
	int status = EXIT_SUCCESS;

	if (args[0] == NULL)
		return (EXIT_SUCCESS);

	if (args[0][0] == '/' || args[0][0] == '.' || strchr(args[0], '/'))
		command_path = args[0];
	else
		command_path = find_command_path(args[0]);

	if (command_path == NULL)
	{
		print_error(program_name, args[0]);
		return (127);
	}

	pid = fork();

	if (pid == 0)
		execute_child(command_path, args, program_name);
	else if (pid < 0)
	{
		perror(program_name);
		status = EXIT_FAILURE;
	}
	else
		status = handle_parent(pid, program_name);

	if (command_path != args[0])
		free(command_path);

	return (status);
}

/**
 * print_error - Print an error message for command not found
 * @program_name: Name of the shell program
 * @command: Command that was not found
 */
void print_error(char *program_name, char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
}
