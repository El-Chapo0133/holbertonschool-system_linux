#include <stdio.h>

void handler(int signal)
{
	printf("Gotcha\n");
}

int handle_signal(void)
{
	signal(SIGINT, handler);

	return (0);
}
