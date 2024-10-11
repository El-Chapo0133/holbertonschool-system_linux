#include "signals.h"

/**
 * handler - handler function for sigint
 * @signal: signal number
 *
 * Return: void
 */
void handler(int signal)
{
	printf("Gotcha %d\n", signal);
}

/**
 * handle_signal - function to start handling SIGINT signal
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
		return (-1);

	return (0);
}
