/*
 * ==========================================================================
 *
 *       Filename:  7-body.c
 *
 *    Description:  opens an IPv4/TCP socket, and listens to traffic on PORT
 *
 *        Version:  1.0
 *        Created:  14.02.2025 16:08:18
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
 * parse_request - parse http request to print body property
 * @client_fd: client fd
 * @buffer: message buffer
 *
 * Return: 1 on success 0 on failure
 */
int parse_request(int client_fd, char *buffer)
{
	fprintf(stdout, "%s\n", buffer);


	return (send_response(client_fd, RESPONSE_200));
}
