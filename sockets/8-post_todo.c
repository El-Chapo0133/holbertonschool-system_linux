/*
 * ==========================================================================
 *
 *       Filename:  8-post_todo.c
 *
 *    Description:  parse an HTTP request, it’s time to implement our
 *	REST API. Start by handling the POST method for the path /todos
 *
 *        Version:  1.0
 *        Created:  21.02.2025 10:03:34
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
	char *start_line, *method, *path, *header, *body,
	     *key, *value, *save1, *save2;
	int content_length = 0;

	body = strstr(buffer, CRLF CRLF);
	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buffer, CRLF, &save1);
	method = strtok(start_line, SP);
	/* extract the path */
	path = strtok(NULL, SP);
	path = strtok(path, "?");
	/* in case it's a post to /todos */
	if (strcasecmp(method, METHOD_POST) || strcasecmp(path, PATH_TODOS))
		return (send_response(client_fd, RESPONSE_404));
	fprintf(stdout, "Path: %s\n", path);
	/* start with the headers just after */
	header = strtok_r(NULL, CRLF, &save1);
	while (header)
	{
		/* extract the key and the value between the ":" */
		key = trim(strtok_r(header, ":", &save2));
		value = trim(strtok_r(NULL, CRLF, &save2));
		/* in case the key is Content-Length, store the value */
		if (!strcasecmp(key, CONTENT_LENGTH))
			content_length = atoi(value);
		/* call for the next header */
		header = strtok_r(NULL, CRLF, &save1);
	}
	if (!content_length)
		return (send_response(client_fd, RESPONSE_411));
	return (post_request(client_fd, body, content_length));
}

/**
 * post_request - parse post request
 * @client_fd: client fd
 * @body: request body
 * @content_length: body length
 *
 * Return: 0 on success 1 on failure
 */
int post_request(int client_fd, char *body, int content_length)
{
	static int ids;
	static todo_t *todo_head;
	char *query, *key, *value, *save1, *save2,
	     *title = NULL, *desc = NULL;
	char buffer1[2048] = {0}, buffer2[1024] = {0};
	todo_t *todo, *node;

	body[content_length] = 0; /* end-of-buffer null char */
	query = strtok_r(body, "&", &save1);
	while (query)
	{
		key = strtok_r(query, "=", &save2);
		value = strtok_r(NULL, "=", &save2);
		fprintf(stdout, "Body param: \"%s\" -> \"%s\"\n", key, value);
		if (!strcasecmp(key, KEY_TITLE))
			title = value;
		else if (!strcasecmp(key, KEY_DESCRIPTION))
			desc = value;
		query = strtok_r(NULL, "&", &save1);
	}
	if (!title || !desc)
		return (send_response(client_fd, RESPONSE_422));

	todo = malloc(sizeof(*todo));
	if (!todo)
		return (EXIT_FAILURE);
	todo->id = ids++;
	todo->title = strdup(title);
	todo->description = strdup(desc);
	if (!todo_head)
		todo_head = todo;
	else
	{
		node = todo_head;
		while (node->next)
			node = node->next;
		node->next = todo;
	}

	sprintf(buffer2, "{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
			KEY_DESCRIPTION "\":\"%s\"}", ids - 1, title, desc);
	sprintf(buffer1, RESPONSE_201 CRLF CONTENT_LENGTH ": %lu" CRLF
			CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s",
			strlen(buffer2), buffer2);
	return (send_response(client_fd, buffer1));
}
