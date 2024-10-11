#ifndef SIGNALS
#define SIGNALS

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);


#endif
