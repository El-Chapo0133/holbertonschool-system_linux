#include "signals.h"


int main(int argc, char **argv)
{
	char *signal;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (-1);
	}
	signal = strsignal(atoi(argv[1]));
	if (signal)
		printf("%s: %s\n", argv[1], signal);
	else
		printf("Unknown signal %s\n", argv[1]);
	return (0);
}
