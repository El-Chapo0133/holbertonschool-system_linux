/*
 * ==========================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  create a socket server
 *
 *        Version:  1.0
 *        Created:  14.02.2025 09:02:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "socket.h"

/**
 * start_server - fully starts a socket server
 * opens and binds socket to accept messages
 * 
 * Return: 0 on failure
 */
int start_server(void)
{
	struct sockaddr_in server;
	int socket_fd;

	setbuf(stdout, NULL);
	/* create the socket */
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		fprintf(stderr, "Socket creation failed");
		return (EXIT_FAILURE);
	}

	/* set server properties */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = hton(INADDR_ANY); /* accept any in-address */
	/* bind the fd to a socket */
	if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) > 0)
	{
		fprintf(stderr, "Socket bind failure");
		close(socket_fd);
		return (EXIT_FAILURE);
	}
	/* start listening, with a maxqueue of BACKLOG (see man listen) */
	if (listen(socket_fd, BACKLOG) < 0)
	{
		fprintf(stderr, "Listen failure");
		close(socket_fd);
		return (EXIT_FAILURE);
	}
	fprintf(stdout, "Server binded and listening on port: %d\n", ntohs(server.sin_port));
	while (1)
		accept_messages(socket_fd);
	close(socket_fd);
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
	struct sockaddr_int client;
	socklen_t client_size = sizeof(client);
	char buffer[MESSAGE_BUFFER_SIZE + 1] = {0};
	ssize_t bytes_read;

	/* accept client and save the fd */
	client_fd = accept(socket_fd, (struct sockaddr *)&client, &client_size);
	if (client_fd < 0)
	{
		fprintf("Accept failure, socket fd: %d", socket_fd);
		return (EXIT_FAILURE);
	}

	/* stdout client address */
	inet_ntop(AD_INET, &client.sin_addr, buffer, INET_ADDRSTRLEN);
	fprintf(strout, "Client connected: %s\n", buffer);

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
