#include "transform_endian.h"

/**
 * get_byte_big_endian -  fetches the bytes in big endian formatted data
 * @data: data to be fetched
 * @size: size of the data
 *
 * Return: the bytes in big endian format data.
 */
uint64_t get_byte_as_little_endian(unsigned char fifth_magic, uint64_t data, int size)
{
	if (fifth_magic == ELFDATA2LSB)
		return (data);

	switch (size)
	{
		case 2:
			return (be16toh(data));
		case 4:
			return (be32toh(data));
		case 8:
			return (be64toh(data));
		default:
			return (0);
	}
}
