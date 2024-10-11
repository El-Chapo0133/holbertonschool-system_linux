#include "signals.h"

void (*current_handler_signal(void))(int)
{
	sighandler_t default_handler = signal(SIGINT, SIG_DFL);

	if (default_handler == SIG_ERR)
		return (NULL);
	else if (signal(SIGINT, default_handler) == SIG_ERR)
		return (NULL);
	return (default_handler);
}
