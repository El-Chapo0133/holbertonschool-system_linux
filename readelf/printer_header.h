#ifndef PRINTER_HEADER
#define PRINTER_HEADER

/**
 * struct Entry - Key and values pair
 * @key : key
 * @value : value
 */
typedef struct Entry
{
	char *key;
	char *value;
} Entry;

#include "_strlen.h"
#include "elfn_ehdr.h"
#include "elf_header_utils_0.h"
#include "elf_header_utils_1.h"
#include <string.h>

void print_elf_header(ElfN_Ehdr ehdr);
void print_magic_number(ElfN_Ehdr ehdr);
void print_all_attributes(ElfN_Ehdr ehdr);
void flatten_elf_header(ElfN_Ehdr ehdr, Entry entries[]);

#endif