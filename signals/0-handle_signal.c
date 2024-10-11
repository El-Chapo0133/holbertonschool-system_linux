#include <stdio.h>

void handler(int signal)
{
	printf("Gotcha %d\n", signal);
}

int handle_signal(void)
{
	signal(SIGINT, handler);

	return (0);
}
