/*
 * ==========================================================================
 *
 *       Filename:  6-headers.c
 *
 *    Description:  opens an IPv4/TCP socket, and listens to traffic on PORT
 *
 *        Version:  1.0
 *        Created:  14.02.2025 14:38:46
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
 * parse_request - parse HTTP header and print fields
 * @client_fd: client fd
 * @buffer: message buffer
 *
 * Return: 1 on success 0 on failure
 */
int parse_request(int client_fd, char *buffer)
{
	char *header, *key, *value, *save1, *save2;

	strtok_r(buffer, CRLF, &save1);
	header = strtok_r(NULL, CRLF, &save1);
	while (header)
	{
		key = trim(strtok_r(header, ":", &save2));
		value = trim(strtok_r(NULL, CRLF, &save2));
		fprintf(stdout, "Header: \"%s\" -> \"%s\"\n", key, value);
		header = strtok_r(NULL, CRLF, &save1);
	}
	send_response(client_fd, RESPONSE_200);
	return (EXIT_SUCCESS);
}
