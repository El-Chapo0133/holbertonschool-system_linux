#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	unsigned long int index;
	char *string;

	string = strdup("Holberton");
	if (string == NULL)
		return (EXIT_FAILURE);
	
	printf("\n\n*    This will run indefinitely         *\n");
	printf("* A SICINT signal is required to end the execution *\n\n\n");
	fflush(NULL);

	for(index = 0; 1; index++)
	{
		printf("[%ld] %s\n", index, string);
		sleep(1);
	}
	return (EXIT_SUCCESS);
}
