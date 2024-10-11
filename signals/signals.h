#ifndef SIGNALS
#define SIGNALS

#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

int handle_signal(void);
void (*current_handler_signal(void))(int);
void (*current_handler_sigaction(void))(int);


#endif
