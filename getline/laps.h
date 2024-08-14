#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
	int id;
	int laps;
	struct Car *next;	
} Car;

void free_cars(void);
void update_cars(int id);
void print_car(void);
void insert_car(int id);
void race_state(int *id, size_t size);
