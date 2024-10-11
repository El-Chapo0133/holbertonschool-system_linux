#include "signals.h"


/**
 * sigint_handler - handler for sigint
 * @sig_no: singal id
 *
 * Return: void
 */
void sigint_handler(int sig_no)
{
	printf("Caught %d\nSignal received\n", sig_no);
}

/**
 * main - this is the main function
 *
 * Return: void
 */
int main(void)
{
	struct sigaction s_action;
	/* clean signals */
	sigemptyset(&s_action.sa_mask);
	s_action.sa_flags = 0;
	s_action.sa_handler = sigint_handler;
	sigaction(SIGINT, &s_action, NULL);

	pause();
	return (EXIT_SUCCESS);
}
