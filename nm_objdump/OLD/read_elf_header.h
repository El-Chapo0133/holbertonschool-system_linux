#ifndef READ_ELF_HEADER
#define READ_ELF_HEADER

#include <stdio.h>
#include <elf.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "transform_endian.h"
#include "elfn_ehdr.h"


#define EXIT_FAILURE 1

void read_elf_header_64(ElfN_Ehdr *ehdr, FILE *file);
void read_elf_header_32(ElfN_Ehdr *ehdr, FILE *file);

#endif