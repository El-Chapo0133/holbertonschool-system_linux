/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description: utils for the whole project 
 *
 *        Version:  1.0
 *        Created:  06.12.2024 09:15:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Lévêque
 *   Organization:  
 *
 * =====================================================================================
 */

#include "strace.h"



/**
 * parse_args - check for args count and if file on argv[1] exists
 * @argc: argc
 * @argv: argv
 *
 * Return: 1 on success 0 on error
 */
int parse_args(int argc, char **argv)
{
	struct stat fs;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", *argv);
		return (0);
	}
	if (stat(argv[1], &fs) == -1)
	{
		fprintf(stderr,
			"%s: Can't stat '%s': No such file or directory\n",
			*argv, argv[1]);
	}
	return (1);
}
