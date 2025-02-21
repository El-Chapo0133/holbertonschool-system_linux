/*
 * ==========================================================================
 *
 *       Filename:  http.h
 *
 *    Description:  http header file
 *
 *        Version:  1.0
 *        Created:  14.02.2025 09:41:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#ifndef H_HTTP
#define H_HTTP

#include <stdio.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 8192 /* 2^13 */
#define BIGGER_BUFFER_SIZE 16284 /* BUFFER_SIZE * 2 */
#define CRLF "\r\n"
#define SP " \t"
#define BACKLOG 8 /* client queue size */

#define RESPONSE_200_NOCRLF "HTTP/1.1 200 OK"
#define RESPONSE_200 (RESPONSE_200_NOCRLF CRLF CRLF)
#define RESPONSE_201 "HTTP/1.1 201 Created"
#define RESPONSE_204 "HTTP/1.1 204 No Content\r\n\r\n"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define RESPONSE_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define RESPONSE_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_LENGTH "Content-Length"
#define URL_ENCODED "application/x-www-form-urlencoded"
#define JSON_TYPE "application/json"

#define PATH_TODOS "/todos"
#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_DELETE "DELETE"

#define KEY_ID "id"
#define KEY_TITLE "title"
#define KEY_DESCRIPTION "description"

/**
 * struct Todo - todo linked list struct
 * @id: todo id
 * @title: todo title
 * @description: todo description
 * @next: next todo in linked list
 */
typedef struct Todo
{
	int id;
	char *title;
	char *description;
	struct Todo *next;
} todo_t;

/*  server */
int start_server(void);
int accept_messages(int sd);
int send_response(int client_sd, char *response);
int parse_request(int client_sd, char *buf);

/* requests */
int post_request(int client_sd, char *body, int content_length);
int get_request(int client_sd);

/*  utils  */
char *trim(char *str);

#endif
