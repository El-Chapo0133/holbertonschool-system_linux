#include "sort.h"
#include "dir_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/**
 * remove_hidden - Replace the items that starts with "." by NULL
 * @count: count of items in array
 * @values: array of items
 *
 * Return: void
 */
void remove_hidden(int count, char* values[count]) {
	int i;
	for (i = 0; i < count; i++) {
		if (values[i][0] == '.') {
			values[i] = NULL;
		}
	}
}

int analyse_folder(char *directory, char ***values) {
	DIR *d;
	struct dirent *dir;
	int index, count;

	d = opendir(directory);
	/* if the directory doesn't exist, the pointer d is NULL
	 * (said in the documentation)
	 * When it occurs, print the error and continue to the next dorectory
	 */
	if (d == NULL) {
		printf("ls: cannot access '%s': No such file or directory\n", directory);
		return (0);
	}
	/* Count the element in dir to create the array, then rewind to the start of the dir */
	count = count_element_in_dir(d);
	*values = malloc(count * sizeof(char*));

	/* fill array with dir elements, no need to check for NULL as we did it earlier */
	index = 0;
	while ((dir = readdir(d)) != NULL) {
		(*values)[index] = dir->d_name;
		index += 1;
	}
	closedir(d);

	/* ls sort the element, so we do */
	sort_strings(count, (*values));
	
	/* unless the flag -a is triggered, we remove every elements that starts with a '.' */
	remove_hidden(count, (*values));

	return (count);
}
