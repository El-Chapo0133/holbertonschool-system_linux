#ifndef PRINTER_PROGRAM_HEADER
#define PRINTER_PROGRAM_HEADER


#include "elfn_ehdr.h"
#include "elfn_shdr.h"
#include "elfn_phdr.h"

void print_header(ElfN_Ehdr ehdr, bool arch32);
void print_type_header(ElfN_Phdr ph_tbl, int fd);
void print_elf_program_header(ElfN_Phdr ph_tbl[], ElfN_Shdr sh_tbl[], ElfN_Ehdr ehdr, int fd);

#endif