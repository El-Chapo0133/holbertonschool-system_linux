#include "hls.h"
#include "analyse_folder.h"
#include "args.h"
#include "displayer.h"
#include "get_lstat.h"
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

/**
 * main - main function
 *
 * Return: 0 (success) or 1 (error)
 */
int main(int argc, char **argv) {
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

		/* analyse the given folder, fill &values with _every_ files/directories in it, fill the &flags if a "-" argument given */
		count = analyse_folder(directories[index_directory], &values, &my_flags);
		if (count == 0)
			continue;

		/* when -l flag is up, fill the array with stat values */
		/* create an array of stat the same length as the values in directory */
		struct stat *stats = malloc(count * sizeof(struct stat*));
		if (my_flags.l == true) {
			int status = get_lstats(count, values, stats);
			if (status != 0) {
				printf("ls: lstats issue - status code: %d\n", status);
				continue;
			}
		}

		/* display the directories with the flags given */
		display(argument_count, index_directory, directories[index_directory], count, values, &my_flags, stats);
	
		/* free values and stats to be re-set */
		free(values);
		free(stats);
	}
	free(directories);

	/* end of programme '\n' */
	// printf("\n");

	return (EXIT_SUCCESS);
}
