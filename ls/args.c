#include "hls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INDEX_FLAG_ONE 0
#define INDEX_FLAG_TINY_A 1
#define INDEX_FLAG_BIG_A 2
#define INDEX_FLAG_L 3

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
 * initialize_flags - initialize the array of flags to false
 * @flags: array of flags
 * 
 * Return: void
 */
void initialize_flags(int **flags) {
	int count = sizeof(flags) / sizeof(int);
	int index;
	for (index = 0; index < count; index++)
		(*flags)[index] = false;
}

/**
 * parse_flags - fill the struct with given chars
 * @arg: list of flags, ex: -la
 * @my_flags: struct to be filled
 *
 * Return: void
 */
void parse_flags(char *arg, int **flags) {
	int index = 0;

	while (arg[index] != '\0') {
		if (arg[index] == '-')
			continue;
		else if (arg[index] == '1')
			(*flags)[INDEX_FLAG_ONE] = true;
		else if (arg[index] == 'a')
			(*flags)[INDEX_FLAG_TINY_A] = true;
		else if (arg[index] == 'A')
			(*flags)[INDEX_FLAG_BIG_A] = true;
		else if (arg[index] == 'l')
			(*flags)[INDEX_FLAG_L] = true;

		index++;
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
int parse_args(int argc, char **argv, char ***directories, int **flags) {
	int index;
	int argument_count = count_arguments(argc, argv);
	
	*directories = malloc(argument_count * sizeof(char*));

	initialize_flags(flags);

	/* start at 1, because [0] is the program argument */
	for (index = 1; index < argc; index++) {
		if (argv[index][0] == '\0')
			continue;
		/* if the args is a flag, parse them */
		else if (is_flags(argv[index]))
			parse_flags(argv[index], flags);
		else
			(*directories)[index - 1] = argv[index];
	}
	/* if no arguments found, use "." */
	if ((*directories)[0] == NULL)
		(*directories)[0] = ".";

	return (argument_count);
}
