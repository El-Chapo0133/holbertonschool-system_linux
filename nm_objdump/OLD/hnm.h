#ifndef HNM
#define HNM

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <elf.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "elf_utils.h"
#include "validate_elf.h"

#define ERROR_ELF_FILE "Error: Not an ELF file - it has the wrong magic bytes at the start"


/**
 * struct ehdr - Struct to represent headers from both 32 and 64bits files
 * @e_ident : magic number
 * @e_entry : Entry point virtual address
 * @e_phoff : Program header table file offset
 * @e_shoff: Section header table file offset
 * @e_version: Identifies object file version
 * @e_flags: Processor-specific flags
 * @e_type: Identifies object file type
 * @e_machine:  Specifies required architecture
 * @e_ehsize:  ELF header size in bytes
 * @e_phentsize:  Program header table entry size
 * @e_phnum:  Program header table entry count
 * @e_shentsize:  Section header table entry size
 * @e_shnum:  Section header table entry count
 * @e_shstrndx: Section header string table index
 */
typedef struct ehdr
{
	unsigned char e_ident[EI_NIDENT];
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_version;
	uint32_t e_flags;
	uint16_t e_type;
	uint16_t e_machine;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} ElfN_Ehdr;

/**
 * struct shdr - Struct to represent section headers from both 32 and 64bits
 * @sh_name : offset to a string in the .shstrtab section that represents the
 * name of this section
 * @sh_type : Identifies the type of this header.
 * @sh_flags : Identifies the attributes of the section.
 * @sh_addr: Virtual address of the section in memory, for sections that are
 * loaded.
 * @sh_offset: Offset of the section in the file image.
 * @sh_size: Size in bytes of the section in the file image. May be 0.
 * @sh_link: Contains the section index of an associated section.
 * @sh_info:  Contains extra information about the section.
 * @sh_addralign:  Contains the required alignment of the section.
 * @sh_entsize:  Contains the size, in bytes, of each entry, for sections that
 * contain fixed-size entries
 */
typedef struct shdr
{
	uint32_t sh_name;
	uint32_t sh_type;
	uint64_t sh_flags;
	uint64_t sh_addr;
	uint64_t sh_offset;
	uint64_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint64_t sh_addralign;
	uint64_t sh_entsize;
} ElfN_Shdr;

/**
 * struct sym - Struct to represent symbole headers from both 32 and 64 bits
 * @st_name: symbole name
 * @st_value: symbole value
 * @st_size: symbole size
 * @st_info: symbole type and binding
 * @st_other: symbole visibility
 * @st_shndx: section index
 */
typedef struct sym
{
	uint32_t st_name;
	uint64_t st_value;
	uint32_t st_size;
	unsigned char st_info;
	unsigned char st_other;
	uint16_t st_shndx;
} ElfN_Sym;


/**
 * elf_header_all_s - struct to contains all elf header infos
 * whatever the endian is
 * @address: address of the mapped memory
 * @is_32: if ELF is 32 bits
 * @is_msb: if ELF is msb
 * @ehdr: Elfn_ehdr
 * @shdr: Elfn_Shdr
 * @sym: Elfn_Sym
 */
typedef struct elf_header_all_s
{
	char *address;
	int is_32;
	int is_msb;
	ElfN_Ehdr *ehdr;
	ElfN_Shdr *shdr;
	ElfN_Sym *sym;
} elf_header_all_t;





#endif
