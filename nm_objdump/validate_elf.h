#ifndef VALIDATE_ELF
#define VALIDATE_ELF

#include <elf.h>
#define true 1
#define false 0

int elf_check_file(unsigned char *magic);
int get_architecture(char c);

#endif
