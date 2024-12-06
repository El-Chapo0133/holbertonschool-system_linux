/*
 * ============================================================================
 *
 *       Filename:  0-strace.c
 *
 *    Description: exo 0 strace 
 *
 *        Version:  1.0
 *        Created:  06.12.2024 09:23:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Lévêque 
 *   Organization:  
 *
 * ============================================================================
 */

#include "strace.h"

void trace_all_sysnums(pid_t pid)
{
	int status;
	struct user_regs_struct regs;

	setbuf(stdout, NULL);

	/* set options of pid to trace syscalls */
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

	while (1)
	{
		waitpid(pid, &status, 0);
		fprintf(stdout, "%d\n", WSTOPSIG(status));
		if (WIFSTOPPED(status) && /* process stopped */
		    WSTOPSIG(status) & 0x80)
			break;

		if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
			break;
		fprintf(stdout, "%lu\n", (long)regs.orig_rax);
	
		/*  resume the process execution */
		if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)
			break;
	}
}


int main(int argc, char **argv)
{
	pid_t pid;
	
	/* check args and if file argv[1] exists */
	if (!parse_args(argc, argv))
		return (EXIT_FAILURE);

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	
	/* replace the process of pid=0 by the one given in argv[1] */
	if (pid == 0)
		return (replace_process(argv + 1) == -1);

	trace_all_sysnums(pid);

	return (EXIT_SUCCESS);
}
