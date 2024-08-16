#include "_getline.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	int fd;
	char *line;

	fd = open("main.c", 0);
	while ((line = _getline(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
