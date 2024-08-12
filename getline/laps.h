#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
	int id;
	int laps;
	struct Car *next;	
} Car;

void free_cars(Car *head);
void update_cars(Car *head, int *id, size_t size);
void print_car(Car *head);
void insert_car(Car *head, int id);
void race_state(int *id, size_t size);
