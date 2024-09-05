#include "_getline.h"



static StreamInformations *stream_informations;

/**
 * _getline - get line of given file
 * @fd: file descriptor to read from
 *
 * Return: char* of the line, NULL if EOF or error
 */
char *_getline(const int fd)
{
	int errors_quantity = 0, position = 0;
	StreamInformations *stream = NULL;
	char *line_ptr = NULL;

	/* error on open() */
	if (fd == -1)
	{
		free_all_stream_informations();
		perror("Cannot open file :(");
		return NULL;
	}

	/* get the correct stream from the fd */
	stream = get_or_create_stream(fd, &errors_quantity);
	/* loop while line hasn't been found */
	while (line_ptr == NULL && stream != NULL && errors_quantity == 0)
	{
		position = 0;

		while ((position < stream->buf_size) && (stream->buf[position] != '\n'))
			position++;

		/* update the buffer */
		if ((position != stream->buf_size) || stream->eof == true)
			line_ptr = get_update_stash(stream, position, &errors_quantity);

		/* set_stash when eof occurs */
		if (stream->eof == false)
			set_stash(stream, &errors_quantity);
	}

	return (line_ptr);
}


/**
 * set_stash - store thestash from the read
 * @stream: The stream to be read
 * @error_occured: flag to indicate malloc errors or any errors.
 */
void set_stash(StreamInformations *stream, int *errors_quantity)
{
	char buf_read[READ_SIZE];
	int bytes_read;
	char *str;

	bytes_read = read(stream->fd, buf_read, READ_SIZE);
	if (bytes_read <= 0)
		stream->eof = 1;
	else
	{
		str = malloc(stream->buf_size + bytes_read);
		if (str)
		{
			if (stream->buf_size)
				memcpy(str, stream->buf, stream->buf_size);
			memcpy(str + stream->buf_size, buf_read, bytes_read);
		}
		else
			errors_quantity++;
		free(stream->buf);
		stream->buf = str;
		stream->buf_size += bytes_read;
	}
}

/**
 * get_update_stash - Returns a string till newline.
 *	and reset the stash with the buffer left.
 * @stream: stream to be searched in
 * @pos: the index where newline occured previously.
 * @error_occured: flag to indicate malloc errors or any errors.
 *
 * Return: A string where till newline occured.
 */
char *get_update_stash(StreamInformations *stream, int pos, int *errors_quantity)
{
	char *str = NULL, *next = NULL;
	int len = stream->buf_size - pos - 1;

	if (stream->buf_size)
	{
		str = malloc(pos + 1);
		if (str)
		{
			memcpy(str, stream->buf, pos);
			str[pos] = 0;
		}
		else
			errors_quantity++;
	}
	stream->buf_size = 0;
	if (len > 0)
	{
		next = malloc(len);
		if (next)
			memcpy(next, stream->buf + pos + 1, len);
		else
			errors_quantity++;
		stream->buf_size = len;
	}
	free(stream->buf);
	stream->buf = next;
	return (str);
}

/**
 * get_or_add_stream - get the stream from his fd, create a new node if no stream found
 * @fd: filedescription used to find stream
 * @error_quantity: quantity of error, incremented when error occurs
 *
 * Return: steam found or created
 */
StreamInformations *get_or_create_stream(int fd, int *error_quantity)
{
	StreamInformations *streams = stream_informations;

	while (streams != NULL && streams->fd == fd)
		streams = streams->next;
	/* of streams is null, add it in front of the linked list */
	if (streams == NULL)
	{
		streams = malloc(sizeof(StreamInformations));
		if (streams == NULL)
		{
			error_quantity++;
			perror("Memory error :(");
			return (NULL);
		}
		/* fill memory with 0s for stream */
		memset(streams, 0, sizeof(*streams));
		streams->fd = fd;
		/* place it in front */
		streams->next = stream_informations;
		stream_informations = streams;
	}

	return (streams);
}

/**
 * free_all_stream_informations - free all buffer and struct of the linked list
 *
 * Return: void
 */
void free_all_stream_informations(void)
{
	StreamInformations *stream = stream_informations;
	StreamInformations *temp_stream;

	while (stream != NULL)
	{
		temp_stream = stream->next;
		free(stream->buf);
		free(stream);
		stream = temp_stream;
	}
}

/**
 * free_stream_informations - update linked list pointers then free given StreamInformations
 * @stream_to_free: given stream to free
 *
 * Return: void
 */
void free_stream_informations(StreamInformations *stream_to_free)
{
	StreamInformations *streams = stream_informations;
	
	/* No streams in linked list */
	if (!streams)
		return;
	/* if the stream to free is the first in linked list */
	else if (stream_to_free == streams)
		stream_informations = streams->next;
	/* find the stream to free and update pointers */
	else
	{
		/* move to the stream to free */
		while (streams->next != stream_to_free && streams != NULL)
			streams = streams->next;
		/* update pointers to prepare the free */
		streams->next = stream_to_free->next;
	}
	
	/* free the buffer, then the struct */
	free(stream_to_free->buf);
	free(stream_to_free);
}
