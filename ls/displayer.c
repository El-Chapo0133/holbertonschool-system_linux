#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void display(int argc, int index_directory, char* directory, int count, char *values[count]) {
	int index;
		
	/**
	 * this block find the max string size (element name + space) length
	 * it will be used to know how many '\t' we must write for each element
	 */
	unsigned long max_str_length = 0;
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) { continue; }
		if (strlen(values[index]) > max_str_length) { max_str_length = strlen(values[index]); }
	}
	max_str_length += abs(((int)max_str_length % 8) - 8);

	/* simple print the elements, ignore the NULL values */
	if (argc > 2)
		printf("%s:\n", directory);
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) { continue; }
		printf("%s", values[index]);
		/* if flag -1 is triggered, print with '\n' */

		/* else print it normally with '\t' */
		if (index < count - 1) {
			int difference_chars = max_str_length - strlen(values[index]);
			int amount_of_tabs = ceil((float)(difference_chars) / 8);
			int j;
			for (j = 0; j < amount_of_tabs; j++) {
				printf("\t");
			}
		}
	}
	/* print an additionnal '\n' if there's more directory to scan */
	if (argc > 2 && index_directory < argc - 2)
		printf("\n");
	/* end of programme '\n' */
	printf("\n");
}
