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
	char *start_line, *path, *header,  *body, *query,
	     *key, *value, *save1, *save2;
	int encoded = 0;

	body = strstr(buffer, CRLF CRLF);
	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buffer, CRLF, &save1);
	/* this is the method, we don't care here */
	strtok(start_line, SP);
	/* extract the path */
	path = strtok(NULL, SP);
	path = strtok(path, "?");
	fprintf(stdout, "Path: %s\n", path);
	/* start with the headers just after */
	header = strtok_r(NULL, CRLF, &save1);
	while (header)
	{
		/* extract the key and the value between the ":" */
		key = trim(strtok_r(header, ":", &save2));
		value = trim(strtok_r(NULL, CRLF, &save2));
		/* in case the value is application/x-www-form-urlencoded */
		if (!strcasecmp(value, URL_ENCODED))
			encoded = 1;
		/* call for the next header */
		header = strtok_r(NULL, CRLF, &save1);
	}

	/* if url is encoded, print the query */
	if (encoded)
	{
		/* start after the "&" */
		query = strtok_r(body, "&", &save1);
		while (query)
		{
			/* get the key before the = */
			key = strtok_r(query, "=", &save2);
			/* get the value and move save2 to next property */
			value = strtok_r(NULL, "?", &save2);
			fprintf(stdout, "Body param: \"%s\" -> \"%s\"\n", key, value);
			/* call for the next property */
			query = strtok_r(NULL, "&", &save1);
		}
	}


	return (send_response(client_fd, RESPONSE_200));
}
