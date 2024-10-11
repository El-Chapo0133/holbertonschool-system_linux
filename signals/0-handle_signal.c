#include "signals.h"

void handler(int signal)
{
	printf("Gotcha %d\n", signal);
}

int handle_signal(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
		return (-1);

	return (0);
}
