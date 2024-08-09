#include "hls.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#ifndef INDEX_FLAG_L
#define INDEX_FLAG_L 3
#endif
#ifndef INDEX_FLAG_ONE
#define INDEX_FLAG_ONE 0
#endif

/**
 * display_normal - Display normal, as columns
 * @count: count of values
 * @values: values in directory
 *
 * Return: void
 */
void display_normal(int count, char **values) {
	int index;

	for (index = 0; index < count; index++) {
		if (values[index] == NULL) { continue; }
		printf("%s\t", values[index]);
	}
	printf("\n");
}
/**
 * display_one - display with \n as separator
 * @count: count of values
 * @values: values in directory
 *
 * Return: void
 */
void display_one(int count, char **values) {
	int index;
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) { continue; }
		printf("%s\n", values[index]);
	}
}
/**
 * display_long - display values in long format, with permissions, links, groupd, owner and modification time
 * @count: count of values
 * @values: values in directory
 * @stats: stats of each values, can be NULL
 *
 * Return: void
 */
void display_long(int count, char **values, struct stat *stats) {
	int index;

	char **group_names = malloc(count * sizeof(char*));
	char **passwd_names = malloc(count * sizeof(char*));
	unsigned short *st_nlinks = malloc(count * sizeof(unsigned short));
	unsigned long *st_sizes = malloc(count * sizeof(unsigned long));

	struct passwd *usr;
	struct group *group;

	/* fill the array */
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) {
			st_nlinks[index] = 0;
			st_sizes[index] = 0;
			passwd_names[index] = "";
			group_names[index] = "";
			continue;
		}
		
		usr = getpwuid(stats[index].st_uid);
		group = getgrgid(stats[index].st_gid);

		st_nlinks[index] = stats[index].st_nlink;
		st_sizes[index] = stats[index].st_size;
		passwd_names[index] = usr->pw_name;
		group_names[index] = group->gr_name;
	}

	for (index = 0; index < count; index++) {
		if (values[index] == NULL)
			continue;

		char *permissions = malloc(11 * sizeof(char));
		permissions[0] = (S_ISDIR(stats[index].st_mode)) ? 'd' : '-';
		permissions[1] = (stats[index].st_mode & S_IRUSR) ? 'r' : '-';
		permissions[2] = (stats[index].st_mode & S_IWUSR) ? 'w' : '-';
		permissions[3] = (stats[index].st_mode & S_IXUSR) ? 'x' : '-';
		permissions[4] = (stats[index].st_mode & S_IRGRP) ? 'r' : '-';
		permissions[5] = (stats[index].st_mode & S_IWGRP) ? 'w' : '-';
		permissions[6] = (stats[index].st_mode & S_IXGRP) ? 'x' : '-';
		permissions[7] = (stats[index].st_mode & S_IROTH) ? 'r' : '-';
		permissions[8] = (stats[index].st_mode & S_IWOTH) ? 'w' : '-';
		permissions[9] = (stats[index].st_mode & S_IXOTH) ? 'x' : '-';

		char *time_str = malloc(10 * sizeof(char));
		strftime(time_str, 10, "%b %H:%M", localtime(&stats[index].st_mtime));

		printf("%s  %d %s %s %lld %s %s\n", permissions, st_nlinks[index], passwd_names[index], group_names[index], st_sizes[index], time_str, values[index]);

		free(permissions);
		free(time_str);
	}
}
void display(int argument_count, int index_directory, char *directory, int count, char **values, int *flags, struct stat *stats) {
	/* if there's many folder to display, print the directory as a header */
	if (argument_count > 1)
		printf("%s:\n", directory);

	if (flags[INDEX_FLAG_ONE] == true) {
		display_one(count, values);
	}
	else if (flags[INDEX_FLAG_L] == true) {
		display_long(count, values, stats);
	}
	else {
		display_normal(count, values);
	}
	

	/* print an additionnal '\n' if there's more directory to scan */
	if (argument_count > 1 && index_directory < argument_count - 1)
		printf("\n");
}
