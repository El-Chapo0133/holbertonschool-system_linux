/*
 * ==========================================================================
 *
 *       Filename:  sockets.h
 *
 *    Description:  header file for the socket project
 *
 *        Version:  1.0
 *        Created:  10.02.2025 12:03:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Levêque (9601), loris@leveque.website
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#ifndef H_SOCKETS
#define H_SOCKETS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> /* for addr formats */
#include <sys/socket.h>
#include <string.h>
#include <netdb.h> /* socket client */
#include <ctype.h>

#define PORT 12345
#define HOST_LEN 256
#define MESSAGE_BUFFER_SIZE 8192 /* 2^13 */
#define BACKLOG 8 /* queue length of clients */

/* Server functions */
int start_server(void);
int accept_messages(int socket_fd);

#endif
