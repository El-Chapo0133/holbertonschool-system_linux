#ifndef ELF_PROGRAM_HEADER_UTILS
#define ELF_PROGRAM_HEADER_UTILS

#include <elf.h>
#include <stdio.h>

char *get_segment_type(unsigned long p_type);

#endif