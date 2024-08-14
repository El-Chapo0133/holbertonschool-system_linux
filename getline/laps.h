#ifndef CAR
#define CAR

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct Car - car node
 * @id: id of the car, unique
 * @laps: amount of laps the car made
 * @next: next car in the linked list
 *
 * Description: Node in a linked list of cars
 */
typedef struct Car
{
	int id;
	int laps;
	struct Car *next;
} Car;

void free_cars(void);
void update_cars(int id);
void print_car(void);
void insert_car(int id);
void race_state(int *id, size_t size);
#endif
