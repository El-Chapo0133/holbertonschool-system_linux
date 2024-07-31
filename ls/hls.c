#include "hls.h"
#include "analyse_folder.h"
#include "args.h"
#include "displayer.h"
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

/**
 * main - main function
 *
 * Return: 0 (success) or 1 (error)
 */
int main(int argc, char *argv[]) {
	int index_directory, argument_count, count;
	char **directories = NULL;
	Flags my_flags;
	my_flags.one = false;
	my_flags.l = false;
	my_flags.a = false;
	my_flags.A = false;

	/* parse the arguments to get the directories and the flags */
	argument_count = parse_args(argc, argv, &directories, &my_flags);
	
	
	for (index_directory = 0; index_directory < argument_count; index_directory++) {
		char **values = NULL;

		count = analyse_folder(directories[index_directory], &values);
		if (count == 0)
			continue;
		display(argument_count, index_directory, directories[index_directory], count, values, &my_flags);
	
		free(values);
	}
	free(directories);

	return (EXIT_SUCCESS);
}
