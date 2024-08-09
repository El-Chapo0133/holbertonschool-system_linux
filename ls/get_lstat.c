#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


int get_lstats(int count, char **values, struct stat *stats) {
	int index, status;

	for (index = 0; index < count; index++) {
		if (values[index] == NULL)
			continue;
		status = lstat(values[index], &stats[index]);
		if (status != 0)
			return (status);
	}

	return (0);
}
