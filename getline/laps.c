#include "laps.h"



static Car *cars;

/**
 * free_cars - free all alocated cars
 *
 * Return: void
 */
void free_cars(void) {
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
void print_cars(void) {
	printf("Race state:\n");
	while (cars != NULL) {
		printf("Car %d [%d laps]\n", cars->id, cars->laps);
		cars = cars->next;
	}
}

/**
 * insert_car - insert a can in the right place of the linked list
 * @head: head of the linked list
 * @id: id to insert
 *
 * Return: void
 */
void insert_car(int id) {
	if (cars == NULL) {
		Car *car = malloc(sizeof(Car));
		car->id = id;
		car->laps = 0;
		car->next = NULL;
		cars = car;
		printf("Car %d joined race\n", id);
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
void update_cars(int *id, size_t size) {
	size_t index;
	int need_to_create_car = 1;
	for (index = 0; index < size; index++) {
		while (cars != NULL) {
			if (id[index] == cars->id) {
				cars->laps++;
				need_to_create_car = 0;
				break;
			}
			cars = cars->next;
		}
		if (need_to_create_car)
			insert_car(id[index]);
	}
}


void race_state(int *id, size_t size) {
	if (size == 0) {
		free_cars();
		return;
	}

	update_cars(id, size);
	
	print_cars();
}

