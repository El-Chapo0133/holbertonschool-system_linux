#include "hls.h"
#include "analyse_folder.h"
#include "args.h"
#include "displayer.h"
#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

/**
 * main - main function
 *
 * Return: 0 (success) or 1 (error)
 */
int main(int argc, char *argv[]) {
	//DIR *d;
	//struct dirent *dir;
	int index_directory, argument_count, count;
	//int argument_count = argc - 1;
	//if (argument_count == 0)
	//	argument_count = 1;
	// detect if - argument found, if yes argument_count--;
	char **directories = NULL;

	/* parse the arguments to get the directories and the flags */
	argument_count = parse_args(argc, argv, &directories);
	for (index_directory = 0; index_directory < argument_count; index_directory++) {
		char **values = NULL;

		count = analyse_folder(directories[index_directory], &values);
		if (count == 0)
			continue;
		display(argc, index_directory, directories[index_directory], count, values);
	}

	return (EXIT_SUCCESS);
}
