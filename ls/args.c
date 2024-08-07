#include "hls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * is_flag - get if a string is a flag (starts with '-')
 * @arg: value to check
 *
 * Return: 1=true 0=false
 */
int is_flags(char *arg) {
	if (arg[0] == '\0')
		return false;
	else if (arg[0] == '-')
		return true;
	return false;
}

/**
 * parse_flags - fill the struct with given chars
 * @arg: list of flags, ex: -la
 * @my_flags: struct to be filled
 *
 * Return: void
 */
void parse_flags(char *arg, Flags *my_flags) {
	int index = 0;
	int length = strlen(arg);

	for (index = 0; index < length; index++) {
		if (arg[index] == '-')
			continue;
		else if (arg[index] == '1')
			my_flags->one = true;
		else if (arg[index] == 'a')
			my_flags->a = true;
		else if (arg[index] == 'A')
			my_flags->A = true;
		else if (arg[index] == 'l')
			my_flags->l = true;
	}	
}

/**
 * count_arguments - count the amount of valid arguments
 * @argc: argc
 * @argv: argv
 *
 * Return: count of valid arguments
 */
int count_arguments(int argc, char *argv[]) {
	int argument_count = 0;
	int index;

	for (index = 1; index < argc; index++) {
		if (argv[index] != NULL && argv[index][0] != '-')
			argument_count++;
	}
	/* means no argument given : use "." */
	if (argument_count == 0)
		argument_count++;

	return (argument_count);
}

/**
 * parse_args - parse argv to a list of arguments, fill the struct Flags with the declared flags
 * @argc: main argc
 * @argv: main argv
 * @directories: array to be filled with directories
 * @arg_flags: flags to be filled
 *
 * Return: quantity of directories 
 */
int parse_args(int argc, char **argv, char ***directories, Flags *arg_flags) {
	int index;
	int argument_count = count_arguments(argc, argv);
	
	*directories = malloc(argument_count * sizeof(char*));

	/* start at 1, because [0] is the program argument */
	for (index = 1; index < argc; index++) {
		if (argv[index][0] == '\0')
			continue;
		/* if the args is a flag, parse them */
		else if (is_flags(argv[index]))
			parse_flags(argv[index], arg_flags);
		else
			(*directories)[index - 1] = argv[index];
	}
	/* if no arguments found, use "." */
	if ((*directories)[0] == NULL)
		(*directories)[0] = ".";

	return (argument_count);
}
