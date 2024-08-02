#include <string.h>
#include <stdlib.h>


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

void sort_strings(int count, char *values[count]) {
	qsort(values, count, sizeof(values[0]), my_strcmp);
}
