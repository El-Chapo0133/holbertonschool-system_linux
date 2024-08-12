#include "laps.h"


void print_cars(Car *head) {
	printf("Race state:\n");
	while (head != NULL) {
		printf("Car %d [%d laps]", head->id, head->laps);
	}
}

void update_cars(Car *head, int *id, size_t size) {
	size_t indexcars;
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

void insert_car(Car *head, int id) {
	while (head != NULL) {
		if (head->id > id) {
			Car *temp = malloc(sizeof(*Car));
			temp->id = id;
			temp->laps = 0;
			temp->next = head->next;
			head->next = temp;
			printf("Car %d joined race", id);
			return;
		}
		else if (head->next == NULL) {
			/* biggest id ever yet */
			Car *temp = malloc(sizeof(*Car));
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

void race_state(int *id, size_t size) {
	static Car cars;
	if (cars == NULL) {
		fprintf("Memory error :(");
		exit(1);
	}

	update_cars(cars, id, size);
	
	print_cars(cars);
}


int main(void) {
	int ids1[3] = {1, 42, 101};
    int ids2[1] = {11};

    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);

}
