#ifndef READ_ELF_PROGRAM_HEADER
#define READ_ELF_PROGRAM_HEADER

#include <elf.h>
#include <assert.h>
#include "transform_endian.h"
#include "read_elf_section.h"
#include "elfn_ehdr.h"
#include "elfn_shdr.h"
#include "elfn_phdr.h"
#include "printer_program_header.h"


void read_elf_program_header_32(ElfN_Ehdr ehdr, ElfN_Phdr *ph_tbl, int fd);
void read_elf_program_header_64(ElfN_Ehdr ehdr, ElfN_Phdr *ph_tbl, int fd);
void read_elf_program_header(ElfN_Ehdr *ehdr, FILE *file, int arch);

#endif