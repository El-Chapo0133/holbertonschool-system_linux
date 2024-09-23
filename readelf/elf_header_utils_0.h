#ifndef ELF_HEADER_UTILS_0
#define ELF_HEADER_UTILS_0

#include <elf.h>
#include <stdio.h>
#include <string.h>

char *get_elf_class(unsigned int elf_class);
char *get_data_encoding(unsigned int encoding);
char *get_elf_version(unsigned int version);
char *get_osabi_name(unsigned int osabi);
char *get_file_type(unsigned int e_type);

#endif