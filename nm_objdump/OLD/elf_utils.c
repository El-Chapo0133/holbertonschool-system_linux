#include "elf_utils.h"


/**
 * convert_msb - convert a big-endian str to a little-endian str
 * @str: str to convert
 * @size: length of str
 *
 * Return: void
 */
void convert_msb(char *str, size_t size)
{
	size_t start = 0, end = size - 1;

	for (; start < end; start++, end--)
	{
		/* classic switch */
		str[start] ^= str[end];
		str[end] ^= str[start];
		str[start] ^= str[end];
	}
}
