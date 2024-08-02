#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
	DIR *dir;
	dir = opendir(".");
	struct dirent *read;
	// struct stat buf;

	char *directories[99];
	struct stat stats[99];

	int index = 0;
	while ((read = readdir(dir)) != NULL) {
		printf("%s\n", read->d_name);
		int temp = lstat(read->d_name, &stats[index]);
		if (temp != 0)
			printf("%d\n", temp);
		directories[index] = read->d_name;
		index++;
	}

	closedir(dir);

	for (index = 0; index < 99; index++) {
		if (directories[index] == NULL)
			continue;
		printf("%s - %d\n", directories[index], stats[index].st_mode);
	}

	return (0);
}
