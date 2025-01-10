#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - Split a string into multiple strings
 * @line: line to be splitted
 * Return: pointer to tokens
 */

char **split_line(char *line)
{
	int bufsize = 64;
	int position = 0;
	/*Allocating memory for passing arguments*/
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;


	if (!tokens) /*Check for memory allocation failure*/
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \n"); /*Split the line by spaces and newlines*/
	while (token != NULL)
	{
		tokens[position++] = token; /*Add the token to the array*/


		if (position >= bufsize) /*If the array is full, reallocate more memory*/
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));

			if (!tokens) /*Check for memory reallocation failure*/
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \n"); /*Continue splitting*/
	}

	tokens[position] = NULL; /*Terminate the array with NULL*/
	return (tokens); /*Return the array of tokens*/
}
