#ifndef VALIDATE_ELF
#define VALIDATE_ELF

#define true 1
#define false 0

int elf_check_file(unsigned char *magic);
int get_architecture(char c);

#endif