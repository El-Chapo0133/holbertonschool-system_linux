#include <stdio.h>
#include <string.h>

int get_max_int(int count, int values[count]) {
	if (count == 0)
		return (0);
	if (count == 1)
		return (values[0]);
	int max = values[0];
	int index;
	for (index = 1; index < count; index++) {
		if (values[index] > max)
			max = values[index];
	}
	return (max);
}
long long int get_max_long_long_int(int count, long long int values[count]) {
	if (count == 0)
		return (0);
	if (count == 1)
		return (values[0]);
	long long int max = values[0];
	int index;
	for (index = 1; index < count; index++) {
		if (values[index] > max)
			max = values[index];
	}
	return (max);
}
int get_max_string(int count, char *values[count]) {	
	if (count == 0)
		return (0);
	if (count == 1)
		return (strlen(values[0]));

	int index, max = strlen(values[0]);
	for (index = 1; index < count; index++) {
		int string_length = strlen(values[index]);
		if (string_length > max)
			max = string_length;
	}
	return (max);
}
