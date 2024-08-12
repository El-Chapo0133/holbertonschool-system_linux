#include "laps.h"

/**
 * free_cars - free all alocated cars
 *
 * Return: void
 */
void free_cars(Car *cars) {
	while (cars != NULL) {
		Car *temp = cars;
		cars = cars->next;
		free(temp);
	}
}

/**
 * print_cars - print all cars in the linked list
 * @head: head of the linked list
 *
 * Return: void
 */
void print_cars(Car *cars) {
	printf("Race state:\n");
	while (cars != NULL) {
		printf("Car %d [%d laps]", cars->id, cars->laps);
	}
}

/**
 * insert_car - insert a can in the right place of the linked list
 * @head: head of the linked list
 * @id: id to insert
 *
 * Return: void
 */
void insert_car(Car *cars, int id) {
	if (cars == NULL) {
		Car *car = malloc(sizeof(Car));
		car->id = id;
		car->laps = 0;
		car->next = NULL;
		cars = car;
		return;
	}
	while (cars != NULL) {
		if (cars->id > id) {
			Car *temp = malloc(sizeof(Car));
			temp->id = id;
			temp->laps = 0;
			temp->next = cars->next;
			cars->next = temp;
			printf("Car %d joined race", id);
			return;
		}
		else if (cars->next == NULL) {
			/* biggest id ever yet */
			Car *temp = malloc(sizeof(Car));
			temp->id = id;
			temp->laps = 0;
			temp->next = NULL;
			cars->next = temp;
			printf("Car %d joined race", id);
			return;
		}
		cars = cars->next;
	}
}
void update_cars(Car *cars, int *id, size_t size) {
	size_t index;
	for (index = 0; index < size; index++) {
		while (cars != NULL) {
			if (id[index] == cars->id) {
				cars->laps++;
				break;
			}
			cars = cars->next;
		}
		insert_car(cars, id[index]);
	}
}


void race_state(int *id, size_t size) {
	static Car *cars;

	if (size == 0) {
		free_cars(cars);
		return;
	}

	update_cars(cars, id, size);
	
	print_cars(cars);
}

