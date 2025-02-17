#include "signals.h"

/**
 * main - this is the main function
 * @argc: argc
 * @argv: argv
 *
 * Return: exit code
 */
int main(int argc, char **argv)
{
	char *signal;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	signal = strsignal(atoi(argv[1]));
	if (signal)
		printf("%s: %s\n", argv[1], signal);
	else
		printf("Unknown signal %s\n", argv[1]);
	return (EXIT_SUCCESS);
}
