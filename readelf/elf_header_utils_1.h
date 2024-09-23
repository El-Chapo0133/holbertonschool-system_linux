#ifndef ELF_HEADER_UTILS_1
#define ELF_HEADER_UTILS_1

#include <elf.h>
#include <stdio.h>
#include <string.h>

char *get_vma(unsigned int no, char format, char end);
char *get_machine_name(unsigned int e_machine);

#endif