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
	int pid;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	pid = atoi(argv[1]);

	if (kill(pid, SIGINT) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
