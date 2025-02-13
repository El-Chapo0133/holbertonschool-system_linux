/*
 * ==========================================================================
 *
 *       Filename:  0-server.c
 *
 *    Description:  connects to a listening server
 *
 *        Version:  1.0
 *        Created:  10.02.2025 12:06:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "sockets.h"

/**
 * close_and_exit - close the given fd and exit(1)
 * @fd: fd to close
 *
 * Return: void
 */
void close_and_exit(int fd)
{
	close(fd);
        freeaddrinfo(res);
	exit(1);
}

/**
 * main - main function
 *
 * Return: return code
 */
int main(int argc, char **argv)
{
        int socket_fd;
        char host[HOST_LEN];
        struct addrinfo hints, *res;

        if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", *argv);
		return (EXIT_FAILURE);
	}

	if (gethostname(host, HOST_LEN) == -1)
		return (EXIT_FAILURE);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host, argv[2], &hints, &res) != 0)
		return (EXIT_FAILURE);
	socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (socket_fd == -1)
		error(socket_fd, res);
	if (connect(socket_fd, res->ai_addr, res->ai_addrlen) == -1)
		error(socket_fd, res);
	printf("Connected to %s:%s\n", argv[1], argv[2]);
	freeaddrinfo(res);
	close(socket_fd);
	return (EXIT_SUCCESS);
}
