#include "hls.h"
#include "my_maths.h"
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


void display_normal(int count, char *values[count]) {
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
}
void display_one(int count, char *values[count]) {
	int index;
	for (index = 0; index < count; index++) {
		if (values[index] == NULL) { continue; }
		printf("%s", values[index]);
		
		if (index < count - 1) { printf("\n");}
	}
}
void display_long(int count, char *values[count], struct stat stats[count]) {
	int index;

	

	for (index = 0; index < count; index++) {
		if (values[index] == NULL)
			continue;
		
		char permissions[11];
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

		char time_str[10];
		strftime(time_str, 10, "%b %H:%M", localtime(&stats[index].st_mtime));
	
		struct passwd *usr = getpwuid(stats[index].st_uid);
		struct group *group = getgrgid(stats[index].st_gid);

		printf("%s  %d %s %s %lld %s %s\n", permissions, stats[index].st_nlink, usr->pw_name, group->gr_name, stats[index].st_size, time_str, values[index]);
	}
}
void display(int argument_count, int index_directory, char *directory, int count, char *values[count], Flags *my_flags, struct stat stats[count]) {
	/* if there's many folder to display, print the directory as a header */
	if (argument_count > 1)
		printf("%s:\n", directory);
	
	if (my_flags->one == true) {
		display_one(count, values);
	}
	else if (my_flags->l == true) {
		display_long(count, values, stats);
	}
	else {
		display_normal(count, values);
	}
	

	/* print an additionnal '\n' if there's more directory to scan */
	if (argument_count > 1 && index_directory < argument_count - 1)
		printf("\n");
	/* end of programme '\n' */
	printf("\n");
}
