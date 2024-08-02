#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int get_max_int(int count, unsigned short values[count]) {
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
long long get_max_long_long_int(int count, unsigned long long values[count]) {
	if (count == 0)
		return (0);
	if (count == 1)
		return (values[0]);
	unsigned long long max = values[0];
	int index;
	for (index = 1; index < count; index++) {
		printf("%llu\n", values[index]);
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
		if (values[index] == NULL) { continue; }
		int string_length = strlen(values[index]);
		if (string_length > max)
			max = string_length;
	}
	return (max);
}
int get_length_of_int(int value) {
	return (floor(log10(abs(value))) + 1);
}
int get_length_of_long_long_int(long long int value) {
	return (floor(log10(llabs(value))) + 1);
}
