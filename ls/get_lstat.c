#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


int get_lstats(char **values, struct stat *stats) {
	int count = sizeof(values) / sizeof(values[0]);
	int index, status;

	for (index = 0; index < count; index++) {
		if (values[index] == NULL)
			continue;
		// (*stats)[index] = (struct stat*)malloc(sizeof(struct stat*));
		status = lstat(values[index], &stats[index]);
		if (status != 0)
			return (status);
	}

	return (0);
}
