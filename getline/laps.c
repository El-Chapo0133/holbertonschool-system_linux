#include "laps.h"

static Car *cars;

/**
 * free_cars - free all alocated cars
 *
 * Return: void
 */
void free_cars(void)
{
	Car *temp;

	while (cars != NULL)
	{
		temp = cars;
		cars = cars->next;
		free(temp);
	}
}

/**
 * print_cars - print all cars in the linked list
 *
 * Return: void
 */
void print_cars(void)
{
	Car *head = cars;

	printf("Race state:\n");
	while (head != NULL)
	{
		printf("Car %d [%d laps]\n", head->id, head->laps);
		head = head->next;
	}
}

/**
 * insert_car - insert a can in the right place of the linked list
 * @id: id to insert
 *
 * Return: void
 */
void insert_car(int id)
{
	Car *new_car = malloc(sizeof(Car));
	Car *head = cars;

	new_car->id = id;
	new_car->laps = 0;
	printf("Car %d joined the race\n", id);

	/* When it's the first node to be added or the first sorted node */
	if (head == NULL || head->id > id)
	{
		new_car->next = cars;
		cars = new_car;
	}
	else
	{
		while (head->next != NULL && head->next->id < id)
		{
			head = head->next;
		}
		new_car->next = head->next;
		head->next = new_car;
	}
}

/**
 * update_cars - update the cars with laps, insert if needed
 * @id: id of laps or insert
 *
 * Return: void
 */
void update_cars(int id)
{
	int need_to_create_car = 1;

	Car *head = cars;

	while (head != NULL)
	{
		if (id == head->id)
		{
			head->laps++;
			need_to_create_car = 0;
			break;
		}
		head = head->next;
	}
	if (need_to_create_car)
		insert_car(id);
}

/**
 * race_state - function asked "race_state"
 * @id: array of id to laps or insert
 * @size: size of the array id
 *
 * Return: void
 */
void race_state(int *id, size_t size)
{
	size_t index;

	if (size == 0)
	{
		free_cars();
		return;
	}

	for (index = 0; index < size; index++)
	{
		update_cars(id[index]);
	}

	print_cars();
}

