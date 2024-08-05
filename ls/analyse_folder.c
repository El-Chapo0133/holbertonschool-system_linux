#include "hls.h"
#include "dir_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/**
 * remove_hidden - Replace the items that starts with "." by NULL
 * @count: count of items in array
 * @values: array of items
 *
 * Return: void
 */
void remove_hidden(int count, char* values[count]) {
	int index;
	for (index = 0; index < count; index++)
		if (values[index][0] == '.')
			values[index] = NULL;
}

/**
 * remove_dot_and_dotdot - Replace the items "." and ".." by NULL
 * @count: count of items in array
 * @values: array of items
 *
 * Return: void
 */
void remove_dot_and_dotdot(int count, char* values[count]) {
	int index;
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) continue;
		if (strcmp(values[index], ".") == 0 || strcmp(values[index], "..") == 0)
			values[index] = NULL;
	}
}

/**
 * analyse_folder - analyse the given folder by filling the array with items
 * @directory: folder to analyse
 * @values: array to be filled with items
 * @my_flags: struct to define what filter on the items
 *
 * Return: amount of items found
 */
int analyse_folder(char *directory, char ***values, Flags *my_flags) {
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

	/* unless the flag -a is triggered, we remove every elements that starts with a '.' */
	if (my_flags->A == true)
		remove_dot_and_dotdot(count, (*values));
	else if (my_flags->a == false)
		remove_hidden(count, (*values));

	return (count);
}
