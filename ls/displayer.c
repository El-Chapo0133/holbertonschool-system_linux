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


/**
 * display_normal - Display normal, as columns
 * @count: count of values
 * @values: values in directory
 *
 * Return: void
 */
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
/**
 * display_one - display with \n as separator
 * @count: count of values
 * @values: values in directory
 *
 * Return: void
 */
void display_one(int count, char *values[count]) {
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
void display_long(int count, char *values[count], struct stat stats[count]) {
	int index, index_j, difference;	

	char *group_names[count];
	char *passwd_names[count];
	unsigned short st_nlinks[count];
	unsigned long long st_sizes[count];
	int max_group_names, max_passwd_names, max_st_nlinks;
	unsigned long long max_st_sizes;
	int max_length_st_nlinks, max_length_st_sizes;

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
	max_group_names = get_max_string(count, group_names);
	max_passwd_names = get_max_string(count, passwd_names);
	max_st_nlinks = get_max_int(count, st_nlinks);
	max_st_sizes = get_max_long_long_int(count, st_sizes);
	max_length_st_nlinks = get_length_of_int(max_st_nlinks);
	max_length_st_sizes = get_length_of_long_long_int(max_st_sizes);

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

		/* no spaces */	
		// printf("%s  %d %s %s %lld %s %s\n", permissions, st_nlinks[index], passwd_names[index], group_names[index], st_sizes[index], time_str, values[index]);
		printf("%s  ", permissions);
		/* with spaces */
		difference = max_length_st_nlinks - get_length_of_int(st_nlinks[index]);
		// printf("%d - %d", max_length_st_nlinks, difference);
		for (index_j = 0; index_j < difference; index_j++) { printf(" "); }
		printf("%d ", st_nlinks[index]);
		difference = max_passwd_names - strlen(passwd_names[index]);
		for (index_j = 0; index_j < difference; index_j++) { printf(" "); }
		printf("%s  ", passwd_names[index]);
		difference = max_group_names - strlen(group_names[index]);
		for (index_j = 0; index_j < difference; index_j++) { printf(" "); }
		printf("%s  ", group_names[index]);
		difference = max_length_st_sizes - get_length_of_long_long_int(st_sizes[index]);
		for (index_j = 0; index_j < difference; index_j++) { printf(" "); }
		printf("%llu ", st_sizes[index]);
		printf("%s ", time_str);
		printf("%s\n", values[index]);
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
	//printf("\n");
}
