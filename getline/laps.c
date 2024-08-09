#include <stdio.h>

int find_free_id(int *cars) {
	int index;
	int length = sizeof(cars) / sizeof(int);
	
	for (index = 0; index < length; index++)
		if (cars[index] == 0)
			return index;
	return -1;
}
int find_car(int *cars, int car_to_find) {
	int index;
	int length = sizeof(cars) / sizeof(int);
	
	for (index = 0; index < length; index++)
		if (cars[index] == car_to_find)
			return index;
	return -1;
}

void race_state(int *id, size_t size) {
	static int* cars;
	static int* laps;
	int index;
	int car_index;
	int free_car_index;

	if (cars == NULL)
		cars = malloc(99 * sizeof(int));
	if (laps == NULL)
		laps = malloc(99 * sizeof(int));

	for (index = 0; index < size; index++) {
		car_index = find_car(cars, id[index]);
		if (car_index == -1) {
			free_car_index = find_free_id(cars);
			if (free_car_index == 0)
				exit(1);
			cars[free_car_index] = id[index];
			laps[free_car_index] = 0;
			printf("Car %d joined the race\n", id[index]);
		}
	}

	printf("Race state:\n");
	for (index = 0; index < 99; index++) {
		printf("Car %d [%d laps]\n", cars[index], laps[index]);
	}
}
