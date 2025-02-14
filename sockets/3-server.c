/*
 * ==========================================================================
 *
 *       Filename:  3-server.c
 *
 *    Description:  opens an IPv4/TCP socket, and listens to traffic on PORT
 *
 *        Version:  1.0
 *        Created:  14.02.2025 09:24:17
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
 * main - main function
 *
 * Return: exit code
 **/
int main(void)
{
	struct sockaddr_in server;
	int socket_fd;

	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		fprintf(stderr, "Socket failed");
		return (EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		fprintf(stderr, "Bind failed");
		close(socket_fd);
		return (EXIT_FAILURE);
	}
	if (listen(socket_fd, BACKLOG) < 0)
	{
		fprintf(stderr, "Listen failed");
		close(socket_fd);
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Server listening on port %d\n", ntohs(server.sin_port));
	accept_messages(socket_fd);
	close(socket_fd);
	return (EXIT_SUCCESS);
}

/**
 * accept_messages - accepts messages from a given socket fd
 * @socket_fd: server socket fd
 *
 * Return: 1 on success 0 on failure
 */
int accept_messages(int socket_fd)
{
	int client_fd;
	struct sockaddr_in client;
	socklen_t client_size = sizeof(client);
	char buffer[MESSAGE_BUFFER_SIZE + 1] = {0};
	ssize_t bytes_read;

	/* accept client and save the fd */
	client_fd = accept(socket_fd, (struct sockaddr *)&client, &client_size);
	if (client_fd < 0)
	{
		fprintf(stdout, "Accept failure, socket fd: %d", socket_fd);
		return (EXIT_FAILURE);
	}

	/* stdout client address */
	inet_ntop(AF_INET, &client.sin_addr, buffer, INET_ADDRSTRLEN);
	fprintf(stdout, "Client connected: %s\n", buffer);

	/* receive the message to the buffer */
	bytes_read = recv(client_fd, buffer, MESSAGE_BUFFER_SIZE, 0);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = 0; /* mark end of string */
		fprintf(stdout, "Message received: \"%s\"\n", buffer);
		/* parse message should happens here */
	}

	close(client_fd);
	return (EXIT_SUCCESS);
}
