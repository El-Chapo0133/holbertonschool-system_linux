#ifndef PRINTER_SECTION
#define PRINTER_SECTION

#include "elfn_shdr.h"
#include "elfn_ehdr.h"
#include "read_elf_section.h"
#include "elf_section_utils_0.h"
#include <inttypes.h>
#include <stdio.h>

void print_flag_detials(int arch);
void print_elf_section_header(ElfN_Shdr sh_tbl[], ElfN_Ehdr ehdr, int fd);

#endif