/*
 * ==========================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14.02.2025 10:00:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "http.h"

/**
 * trim - trims leading and trailing whitespace from str
 * @str: the string to trim
 * Return: trimmed string
 */
char *trim(char *str)
{
	ssize_t j;

	if (!str)
		return (NULL);
	while (isspace((unsigned char)*str))
		str++;
	for (j = strlen(str) - 1; j >= 0; j--)
	{
		if (!isspace((unsigned char)str[j]))
			break;
		str[j] = 0;
	}
	return (str);
}
