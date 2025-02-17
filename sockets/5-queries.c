/*
 * ==========================================================================
 *
 *       Filename:  5-queries.c
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
	char *path, *query, *save1, *key, *value, *save2;

	/* Exemple request :
	 * GET /test?value1=holberton&value2=school HTTP/1.1
	 */
	strtok(buffer, delims); /* define buffer in strtok */
	path = strtok(NULL, delims); /* get the path */
	path = strtok_r(path, "?", &save1); /* get after the ? */
	fprintf(stdout, "Path: %s\n", path);
	/* tokenize the query after the ? with & */
	query = strtok_r(NULL, "&", &save1); 
	while (query)
	{
		/* get the key before the = */
		key = strtok_r(query, "=", &save2);
		/* get the value and move save2 to next property */
		value = strtok_r(NULL, "?", &save2);
		fprintf(stdout, "Query: \"%s\" -> \"%s\"\n", key, value);
		/* call for the next property */
		query = strtok_r(NULL, "&", &save1);
	}
	return (send_response(client_fd, RESPONSE_200));
}
