#ifndef ELF_SECTION_UTILS_0
#define ELF_SECTION_UTILS_0

#include <elf.h>
#include <string.h>
#include <stdio.h>
#include "elfn_ehdr.h"

char *get_section_type_name(unsigned int sh_type);
char *get_elf_section_flags(ElfN_Ehdr elf_header, unsigned long sh_flags);

#endif