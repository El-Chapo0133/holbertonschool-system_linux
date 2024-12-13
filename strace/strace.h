/*
 * =====================================================================================
 *
 *       Filename:  strace.h
 *
 *    Description: strace.h 
 *
 *        Version:  1.0
 *        Created:  06.12.2024 09:20:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Lévêque
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STRACE_H
#define STRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/user.h> /* for struct user_regs_struct */
#include <sys/wait.h>

#include "syscalls.h"

/* utils */
int parse_args(int argc, char **argv);
int replace_process(char **argv);
int await_syscall(int pid);
void print_args(const syscall_t *syscall, struct user_regs_struct *regs, int pid);

#endif
