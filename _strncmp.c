#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * _strncmp - Compare Amount (n) Of Characters Of Two Strings.
 * @s1: A String.
 * @s2: A String.
 * @n: Amount Of Characters To Compare.
 *
 * Return: 1 If The Strings Don't Match Otherwise 0
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL)
		return (-1);
	for (i = 0; i < n && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}
