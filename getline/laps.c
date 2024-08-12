#include "laps.h"


void free_cars(Car *head) {
	while (head != NULL) {
		Car *temp = head->next;
		free(head);
		head = temp;
	}
}

void print_cars(Car *head) {
	printf("Race state:\n");
	while (head != NULL) {
		printf("Car %d [%d laps]", head->id, head->laps);
	}
}

void insert_car(Car *head, int id) {
	if (head == NULL) {
		Car *car = malloc(sizeof(Car));
		car->id = id;
		car->laps = 0;
		car->next = NULL;
		head = car;
		return;
	}
	while (head != NULL) {
		if (head->id > id) {
			Car *temp = malloc(sizeof(Car));
			temp->id = id;
			temp->laps = 0;
			temp->next = head->next;
			head->next = temp;
			printf("Car %d joined race", id);
			return;
		}
		else if (head->next == NULL) {
			/* biggest id ever yet */
			Car *temp = malloc(sizeof(Car));
			temp->id = id;
			temp->laps = 0;
			temp->next = NULL;
			head->next = temp;
			printf("Car %d joined race", id);
			return;
		}
		head = head->next;
	}
}
void update_cars(Car *head, int *id, size_t size) {
	size_t index;
	for (index = 0; index < size; index++) {
		while (head != NULL) {
			if (id[index] == head->id) {
				head->laps++;
				break;
			}
			head = head->next;
		}
		insert_car(head, id[index]);
	}
}


void race_state(int *id, size_t size) {
	static Car *cars;

	if (size == 0) {
		free_cars(cars);
		exit(0);
	}

	update_cars(cars, id, size);
	
	print_cars(cars);
}

