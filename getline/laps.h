#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
	int id;
	int laps;
	Car *next;	
} Car;

void race_state(int *id, size_t size);
