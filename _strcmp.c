#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * _strcmp - compare 2 string
 * 
 * @s1: 1st string
 * @s2: 2nd string
 * 
 * Return: 0 if identical
 */

int _strcmp(char *s1, char *s2)
{
int cmp = 0, i, len1, len2;
len1 = _strlen(s1);
len2 = _strlen(s2);

	if (s1 == NULL || s2 == NULL)
		return (1);
	if (len1 != len2)
		return (1);
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			cmp = s1[i] - s2[i];
			break;
		}
		else
			continue;
	}
	return (cmp);
}
