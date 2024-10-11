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
 * current_handler_sigaction - create handler for sigint
 *
 * Return: address of handler
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction s_action;

	sigemptyset(&s_action.sa_mask);
	s_action.sa_flags = 0;
	s_action.sa_handler = sigint_handler;
	return (sigaction(SIGINT, NULL, &s_action) ? NULL : s_action.sa_handler);
	/*
	if (sigaction(SIGINT, &s_action, NULL) == 0)
		return (NULL);
	return (s_action.sa_handler);
	*/
}
