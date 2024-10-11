#include "signals.h"


/**
 * current_handler_signal - function to start handling SIGINT
 *
 * Return: NULL on error, handler address on success
 */
void (*current_handler_signal(void))(int)
{
	/* this is void (*)(int) */
	sighandler_t default_handler = signal(SIGINT, SIG_DFL);

	if (default_handler == SIG_ERR)
		return (NULL);
	else if (signal(SIGINT, default_handler) == SIG_ERR)
		return (NULL);
	return (default_handler);
}
