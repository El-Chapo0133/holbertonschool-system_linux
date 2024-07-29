#include "hls.h"
#include "dir_utils.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

/**
 * count_element_in_dir - count element in directory *d, then rewind
 * @d: DIR where to count element
 *
 * Return: quantity of element in DIR
 */
/*int count_element_in_dir(DIR *d) {
	int result = 0;
	while (readdir(d) != NULL) { result += 1; }
	rewinddir(d);
	return (result);
}*/

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
 * my_strcmp - fonction of two string comparison, supposed to be used with qsort
 * @a: first string
 * @b: second string
 *
 * Return: 0 or 1
 */
int my_strcmp(const void* a, const void* b) {
	return strcmp(*(const char**)a, *(const char**)b);
}

/**
 * main - main function
 *
 * Return: 0 (success) or 1 (error)
 */
int main(void) {
	DIR *d;
	struct dirent *dir;
	int i, count;

	d = opendir(".");

	count = count_element_in_dir(d);
	char *values[count];

	if (d) {
		i = 0;
		while ((dir = readdir(d)) != NULL) {
			values[i] = dir->d_name;
			i += 1;
		}
		closedir(d);
	}

	qsort(values, count, sizeof(values[0]), my_strcmp);

	remove_hidden(count, values);


	for (i = 0; i < count; i++) {
		if (values[i] == NULL) { continue; }
		printf("%s", values[i]);
		if (i < count - 1) { printf("\t"); }
	}
	printf("\n");

	return (EXIT_SUCCESS);
}
