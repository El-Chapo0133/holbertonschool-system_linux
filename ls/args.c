#include <stdio.h>
#include <stdlib.h>

/* add struct *Flags */
int parse_args(int argc, char *argv[], char ***directories) {
	int index;
	int argument_count = argc - 1;
	if (argument_count == 0)
		argument_count = 1;
	// detect if - argument found, if yes argument_count--;
	*directories = malloc(argument_count * sizeof(char*));
	
	if (argc == 1)
		(*directories)[0] = ".";
	else
		for (index = 1; index < argc; index++)
			(*directories)[index - 1] = argv[index];

	return (argument_count);
}

/*
void detect_flags() {}
void parse_flags() {}
*/
