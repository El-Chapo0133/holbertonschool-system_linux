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

	waitpid(pid, &status, 0);
	/* set options of pid to trace syscalls */
 	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(pid))
			break;

		memset(&regs, 0, sizeof(regs));
		if (ptrace(PTRACE_GETREGS, pid, 0, &regs) != -1)
			fprintf(stdout, "%s",
				syscalls_64_g[(long)regs.orig_rax].name);

		if (await_syscall(pid))
		{
			fprintf(stdout, " = ?\n");
			break;
		}
		else
		{
			memset(&regs, 0, sizeof(regs));
			if (ptrace(PTRACE_GETREGS, pid, 0, &regs) != -1)
				fprintf(stdout, " = %#lx\n", (long)regs.rax);
		}
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
