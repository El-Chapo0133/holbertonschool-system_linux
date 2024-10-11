#include "signals.h"


/**
 * sigquit_handler - handler for sigint
 * @sig_no: singal id
 *
 * Return: void
 */
void sigquit_handler(int sig_no, siginfo_t *siginfo, void *ucontext)
{
	printf("SIGQUIT sent by %d\n", siginfo->si_pid);
	/* remove unused parameters error */
	(void)sig_no;
	(void)ucontext;
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
	s_action.sa_sigaction = sigquit_handler;
	return (sigaction(SIGQUIT, &s_action, NULL));
}
