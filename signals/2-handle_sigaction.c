#include "signals.h"

/**
 * sigint_handler - handler for sigint
 * @sig_no: singal id
 *
 * Return: void
 */
void sigint_handler(int sig_no)
{
	printf("Gotcha %d\n", sig_no);
	fflush(stdout);
}

/**
 * handle_sigaction - create a sigaction for sigint
 *
 * Return: 0 on success, -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction s_action;
	/* clean signals */
	sigemptyset(&s_action.sa_mask);
	s_action.sa_flags = 0;
	s_action.sa_handler = sigint_handler;
	return (sigaction(SIGINT, &s_action, NULL));
}
