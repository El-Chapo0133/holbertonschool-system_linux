/*
 * ==========================================================================
 *
 *       Filename:  0-server.c
 *
 *    Description:  opens an IPv4/TCP socket, and listens to traffic
 *			on PORT 12345
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
	exit(1);
}

/**
 * main - main function
 *
 * Return: return code
 */
int main(void)
{
	int socket_fd;
	struct sockaddr_in addr, client_addr;
	socklen_t client_addrlen;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		close_and_exit(socket_fd);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		close_and_exit(socket_fd);
	if (listen(socket_fd, 10) == -1)
		close_and_exit(socket_fd);
	printf("Server listening on PORT %i\n", PORT);

	client_addrlen = sizeof(client_addr);
	if (accept(socket_fd, (struct sockaddr *) &client_addr, &client_addrlen) ==
			-1)
		close_and_exit(socket_fd);
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	close(socket_fd);

	return (0);
}
