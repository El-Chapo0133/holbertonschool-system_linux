#ifndef READ_ELF_SECTION
#define READ_ELF_SECTION

#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "elfn_shdr.h"
#include "read_elf_header.h"
#include "printer_section.h"


void read_elf_section_header(ElfN_Ehdr *ehdr, FILE *file, int arch);
void read_elf_section_header_32(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd);
void read_elf_section_header_64(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd);
char *read_section(int fd, ElfN_Shdr sh);

#endif