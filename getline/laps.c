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
	Car *head = cars;

	printf("Race state:\n");
	while (head != NULL) {
		printf("Car %d [%d laps]\n", head->id, head->laps);
		head = head->next;
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
	Car *new_car = malloc(sizeof(Car));
	Car *head = cars;
	new_car->id = id;
	new_car->laps = 0;
	printf("Car %d joined the race\n", id);

	/* When it's the first node to be added */
	if (head == NULL) {
		new_car->next = NULL;
		cars = new_car;
	}
	else {
		while (head != NULL) {
			/* Insert the node at the right place */
			if (head->next != NULL && head->next->id > id) {
				new_car->next = head->next;
				head->next = new_car;
				break;
			}
			/* When it's the end place the node at the end */
			else if (head->next == NULL) {
				new_car->next = NULL;
				head->next = new_car;
				break;
			}
			head = head->next;
		}
	}
}

/**
 * update_cars - update the cars with laps, insert if needed
 * @id: array of id to laps or insert
 * @size: size of the array id
 *
 * Return: void
 */
void update_cars(int *id, size_t size) {
	size_t index;
	int need_to_create_car;

	Car *head = cars;

	for (index = 0; index < size; index++) {
		need_to_create_car = 1;
		while (head != NULL) {
			if (id[index] == head->id) {
				head->laps++;
				need_to_create_car = 0;
				break;
			}
			head = head->next;
		}
		if (need_to_create_car)
			insert_car(id[index]);
	}
}

/**
 * race_state - function asked "race_state"
 * @id: array of id to laps or insert
 * @size: size of the array id
 *
 * Return: void
 */
void race_state(int *id, size_t size) {
	if (size == 0) {
		free_cars();
		return;
	}

	update_cars(id, size);
	
	print_cars();
}

