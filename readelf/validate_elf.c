#include "validate_elf.h"

/**
 * elf_check_file -  checks if the elf file is valid
 * @magic: magic string
 *
 * Return: on success:  true , on Failure: false.
 */
int elf_check_file(unsigned char *magic)
{
	if (magic[0] != ELFMAG0)
		return (false);
	if (magic[1] != ELFMAG1)
		return (false);
	if (magic[2] != ELFMAG2)
		return (false);
	if (magic[3] != ELFMAG3)
		return (false);
	return (true);
}

/**
 * get_architecture -  fetches the architecture of the elf file
 * @c: char
 * @arch: architecture - 32 /64
 *
 * Return: on success:  true , on Failure: false.
 */
int get_architecture(char c)
{
	if (c == ELFCLASS32)
		return (32);
	else if (c == ELFCLASS64)
		return (64);
	return (-1);
}
