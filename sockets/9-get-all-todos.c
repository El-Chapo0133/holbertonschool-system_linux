/*
 * ==========================================================================
 *
 *       Filename:  9-get-all-todos.c
 *
 *    Description:  Handle the GET method for the path /todos
 *
 *        Version:  1.0
 *        Created:  21.02.2025 10:52:06
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
 * Return: 0 on success 1 on failure
*/
int parse_request(int client_fd, char *buffer)
{
	fprintf(stdout, "%s\n", buffer);

	return (send_response(client_fd, RESPONSE_200));	
}
