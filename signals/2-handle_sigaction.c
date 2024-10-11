#include "signals.h"

void sigint_handler(int sig_no)
{
	printf("Gotcha %d\n", sig_no);
}

int handle_sigaction(void)
{
	struct sigaction s_action;
	sigemptyset(&s_action.sa_mask);
	s_action.sa_flags = 0;
	s_action.sa_handler = sigint_handler;
	return (sigaction(SIGINT, &s_action, NULL));
}
