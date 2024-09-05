#ifndef MAIN
#define MAIN
#define READ_SIZE 1024
#define true 1
#define false 0

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * struct stream_s - struct of linked list about informations of specific stream
 * @fd: file description, from an "open()" call
 * @buf: buffer for the fd
 * @buf_size: size of the buffer for the fd
 * @oef: bool of end of file
 * @next: point to next node in linked list
 *
 * Description: node in linked list of streams, should be unique
 */
typedef struct stream_s
{
	int fd;
	char *buf;
	int buf_size;
	int oef;
	struct stream_s *next;
} StreamInformations;

char *_getline(const int fd);
void set_stash(StreamInformations *stream, int *errors_quantity);
char *get_update_stash(StreamInformations *stream, int pos, int *errors_quantity);
StreamInformations *get_or_create_stream(int fd, int *error_quantity);
void free_all_stream_informations(void);
void free_stream_informations(StreamInformations *stream_to_free);

#endif
