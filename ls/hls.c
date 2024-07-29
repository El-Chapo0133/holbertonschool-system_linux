#include "hls.h"
#include <stdio.h>
#include <dirent.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

int count_element_in_dir(DIR *d) {
	int result = 0;
	while (readdir(d) != NULL) { result += 1; }
	rewinddir(d);
	return (result);
}

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
	for (i = 0; i < count; i++) {
		/*if (values[i] == '\0') {
			values[i] = NULL;
		}*/
		if (values[i][0] == '.') {
			values[i] = NULL;
		}
	}

	for (i = 0; i < count; i++) {
		if (values[i] == NULL) { continue; }
		printf("%s", values[i]);
		if (i < count - 1) { printf("\t"); }
	}
	printf("\n");

	return (EXIT_SUCCESS);
}
