#ifndef PRINTER_PROGRAM_HEADER
#define PRINTER_PROGRAM_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "elfn_ehdr.h"
#include "elfn_shdr.h"
#include "elfn_phdr.h"
#include "elf_header_utils_0.h"
#include "read_elf_section.h"
#include "elf_program_header_utils.h"


#define PATH_MAX 512

void print_header(ElfN_Ehdr ehdr, int arch32);
void print_type_header(ElfN_Phdr ph_tbl, int fd);
void print_elf_program_header(ElfN_Phdr ph_tbl[], ElfN_Shdr sh_tbl[], ElfN_Ehdr ehdr, int fd);
int is_elf_section_in_segment(ElfN_Shdr shdr, ElfN_Phdr phdr);
int get_elf_section_size(ElfN_Shdr shdr, ElfN_Phdr phdr);


#endif