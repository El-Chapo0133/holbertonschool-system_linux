/*
 * ==========================================================================
 *
 *       Filename:  4-request.c
 *
 *    Description:  opens an IPv4/TCP socket, and listens to traffic on PORT
 *
 *        Version:  1.0
 *        Created:  14.02.2025 09:42:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "http.h"

/**
 * main - main function
 *
 * Return: exit code
 **/
int main(void)
{
	/* start the server */
	return (start_server());
}

/**
 * parse_request - parse HTTP headers and prints them
 * @client_fd: client fd
 * @buffer: message buffer
 *
 * Return: 1 on success otherwise 0
 **/
int parse_request(int client_fd, char *buffer)
{
	char *delims = " \t\r\n";

	fprintf(stdout, "Method: %s\nPath: %s\nVersion: %s\n",
			strtok(buffer, delims),
			strtok(buffer, delims),
			strtok(buffer, delims));
	return (send_response(client_fd, RESPONSE_200));
}
