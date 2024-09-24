#ifndef HREADELF
#define HREADELF

#include <elf.h>
#include "elfn_ehdr.h"
#include "validate_elf.h"
#include "read_elf_program_header.h"
#include "elfn_ehdr.h"

#define true 1
#define false 0
#define ERROR_ELF_FILE "Error: Not an ELF file - it has the wrong magic bytes at the start"

#endif