#include <stdio.h>

void handler(int signal)
{
	printf("Gotcha %d\n", signal);
}

int handle_signal(void)
{
	int error;
	
	error = signal(SIGINT, handler);

	if (error == SIG_ERR)
		return (-1);
	return (0);
}
