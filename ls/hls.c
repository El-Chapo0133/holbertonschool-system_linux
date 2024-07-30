#include "hls.h"
#include "dir_utils.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

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

/**
 * main - main function
 *
 * Return: 0 (success) or 1 (error)
 */
int main(int argc, char *argv[]) {
	DIR *d;
	struct dirent *dir;
	int index, index_directory, count;
	int argument_count = argc - 1;
	if (argument_count == 0)
		argument_count = 1;
	// detect if - argument found, if yes argument_count--;
	char *directories[argument_count];
		
	if (argc == 1)
		directories[0] = ".";
	else
		for (index = 1; index < argc; index++)
			directories[index - 1] = argv[index];

	sort_strings(argument_count, directories);

	for (index_directory = 0; index_directory < argument_count; index_directory++) {
		d = opendir(directories[index_directory]);
		if (d == NULL) {
			printf("ls: cannot access '%s': No such file or directory\n", directories[index_directory]);
			continue;
		}
		count = count_element_in_dir(d);
		char *values[count];
	
		if (d) {
			index = 0;
			while ((dir = readdir(d)) != NULL) {
				values[index] = dir->d_name;
				index += 1;
			}
			closedir(d);
		}
	
		sort_strings(count, values);
	
		remove_hidden(count, values);
	
		unsigned long max_str_length = 0;
		for (index = 0; index < count; index++) {
			if (values[index] == NULL) { continue; }
			if (strlen(values[index]) > max_str_length) { max_str_length = strlen(values[index]); }
		}
		max_str_length += abs(((int)max_str_length % 8) - 8);
	
		if (argc > 1)
			printf("%s:\n", directories[index_directory]);
		for (index = 0; index < count; index++) {
			if (values[index] == NULL) { continue; }
			printf("%s", values[index]);
			if (index < count - 1) {
				int difference_chars = max_str_length - strlen(values[index]);
				int amount_of_tabs = ceil((float)(difference_chars) / 8);
				int j;
				for (j = 0; j < amount_of_tabs; j++) {
					printf("\t");
				}
			}
		}
		if (argc > 1 && index_directory < argument_count - 1)
			printf("\n");
		printf("\n");
	}
	
	return (EXIT_SUCCESS);
}
