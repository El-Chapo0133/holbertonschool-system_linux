#include "signals.h"


/**
 * sigint_handler - handler for sigint
 * @sig_no: singal id
 *
 * Return: void
 */
void sigint_handler(int sig_no)
{
	printf("SIGQUIT sent by %d\n", siginfo->si_pid);
}

/**
 * trace_signal_sender - create sigaction for SIGQUIT
 *
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction s_action;
	sigemptyset(&s_action.sa_mask);
	/* needed to get pid */
	s_action.sa_flags = SA_SIGINFO;
	/* due to SA_SIGINFO, we muse use sa_sigaction */
	s_action.sa_sigaction = sigint_handler;
	return(sigaction(SIGQUIT, &s_action, NULL));
}
