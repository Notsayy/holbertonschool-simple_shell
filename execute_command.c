#include "shell.h"
/**
 * execute_child_process - Execute the command in the child process
 * @args: Command arguments
 * @program_name: Name of the shell program
 * @command_path: Full path of the command
 */
void execute_child_process(char **args, char *program_name, char *command_path)
{
	if (command_path != NULL)
	{
		execv(command_path, args);
		perror(program_name);
		free(command_path);
		exit(127);
	}
	else
	{
		if (access(args[0], X_OK) == 0)
		{
			execvp(args[0], args);
			perror(program_name);
			exit(127);
		}
		else
		{

			fprintf(stderr, "%s: %s: Command not found\n", program_name, args[0]);
			exit(127);
		}
	}
}


/**
 * wait_for_child - Wait for the child process to complete
 * @pid: Process ID of the child
 * @program_name: Name of the shell program
 * Return: The exit status of the child process, or EXIT_FAILURE.
 */
int wait_for_child(pid_t pid, char *program_name)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror(program_name);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		fprintf(stderr, "%s: Command terminated by signal %d\n",
		program_name, WTERMSIG(status));
		return (128 + WTERMSIG(status));
	}
	return (EXIT_FAILURE);
}

/**
 * execute_command - Forks a new process and executes the command
 * @args: The command to be executed
 * @program_name: Name of the shell program
 * Return: The exit status of the executed command, or 127 if command not found
 */
int execute_command(char **args, char *program_name)
{
	pid_t pid;
	char *command_path;
	int status = EXIT_SUCCESS;

	command_path = find_command_path(args[0]);

	if (args[0][0] != '/' && args[0][0] != '.' && command_path == NULL)
	{
		print_error(program_name, args[0]);
		return (127);
	}

	pid = fork();

	if (pid == 0)
	{
		execute_child_process(args, program_name, command_path);
	}
	else if (pid < 0)
	{
		fprintf(stderr, "%s: Error: Unable to create child process\n", program_name);
		status = EXIT_FAILURE;
	}
	else
	{
		status = wait_for_child(pid, program_name);
	}

	if (command_path != NULL)
	{
		free(command_path);
	}

	return (status);
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
