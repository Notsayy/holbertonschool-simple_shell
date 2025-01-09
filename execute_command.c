#include "shell.h"
/**
 * execute_child_process - Execute the command in the child process
 * @args: Command arguments
 * @program_name: Name of the shell program
 * @command_path: Full path of the command
 */
void execute_child_process(char **args, char *program_name, char *command_path)
{
	if (command_path != NULL) /*If the command was found in PATH, execute it*/
	{
		if (execve(command_path, args, environ) == -1)/*Execute the command*/
		{
			perror(program_name);
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	/*If the command was not found in PATH, check if it's a valid direct path*/
	else
	{
		/*Check if args[0] is a valid file and executable*/
		if (access(args[0], X_OK) == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror(program_name);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/*Command not found or not executable*/
			fprintf(stderr, "%s: %s: Command not found\n", program_name, args[0]);
			exit(127);
		}
	}
}

/**
 * wait_for_child - Wait for the child process to complete
 * @pid: Process ID of the child
 * @program_name: Name of the shell program
 */
void wait_for_child(pid_t pid, char *program_name)
{
	int status;

	do {
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 127)
			{
				fprintf(stderr, "%s: Command not found\n", program_name);
			}
		}
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
/**
 * execute_command - Forks a new process and executes the command
 * @args: The command to be executed
 * @program_name: Name of the shell program
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;
	char *command_path;

	command_path = find_command_path(args[0]);/*Get the full path of the command*/

	if (args[0][0] != '/' && args[0][0] != '.' && command_path == NULL)
	{
		print_error(program_name, args[0]);
		return;
	}

	pid = fork();/*Create a new child process*/

	if (pid == 0)
	{
		/*Execute command in the child*/
		execute_child_process(args, program_name, command_path);
	}
	else if (pid < 0)/*Error handling for fork failure*/
	{
		fprintf(stderr, "%s: Error: Unable to create child process\n", program_name);
	}
	else
	{
		wait_for_child(pid, program_name);/*Wait for the child process*/
	}

	if (command_path != NULL)
	{
		free(command_path);/*Free the allocated memory for the command path*/
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
