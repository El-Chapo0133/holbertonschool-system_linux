#include "read_elf_program_header.h"

/**
 * read_elf_program_header_32 - fills the ph with suitable(32)
 * architecture data
 * @ph_tbl: program header table
 * @fd: file descriptor of input elf file
 * @ehdr: elf header structure
 */
void read_elf_program_header_32(ElfN_Ehdr ehdr, ElfN_Phdr *ph_tbl, int fd)
{
	int index;

	Elf32_Phdr phdr32_table;

	unsigned char fifth_magic = ehdr.e_ident[EI_DATA]; // either 1 or 2

    // move ptr to program header offset
	assert(lseek(fd, (off_t)ehdr.e_phoff, SEEK_SET) == (off_t)ehdr.e_phoff);

    // loop over program header
	for (index = 0; index < ehdr.e_phnum; index++)
	{
        // read program header to phdr32_table
		assert(read(fd, (void *)&phdr32_table, ehdr.e_phentsize) ==
		       ehdr.e_phentsize);

		ph_tbl[index].p_type    = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_type, sizeof(phdr32_table.p_type));
		ph_tbl[index].p_flags   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_flags, sizeof(phdr32_table.p_flags));
		ph_tbl[index].p_offset  = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_offset, sizeof(phdr32_table.p_offset));
		ph_tbl[index].p_vaddr   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_vaddr, sizeof(phdr32_table.p_vaddr));
		ph_tbl[index].p_paddr   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_paddr, sizeof(phdr32_table.p_paddr));
		ph_tbl[index].p_filesz  = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_filesz, sizeof(phdr32_table.p_filesz));
		ph_tbl[index].p_memsz   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_memsz, sizeof(phdr32_table.p_memsz));
		ph_tbl[index].p_flags   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_flags, sizeof(phdr32_table.p_flags));
		ph_tbl[index].p_align   = get_byte_as_little_endian(fifth_magic, 
            phdr32_table.p_align, sizeof(phdr32_table.p_align));
	}
}

/**
 * read_elf_program_header_64- fills the ph with suitable(64)
 * architecture data
 * @ph_tbl: program header table
 * @fd: file descriptor of input elf file
 * @ehdr: elf header structure
 */
void read_elf_program_header_64(ElfN_Ehdr ehdr, ElfN_Phdr *ph_tbl, int fd)
{
	int index;
	Elf64_Phdr phdr64_table;

	unsigned char fifth_magic = ehdr.e_ident[EI_DATA]; // either 1 or 2

    // move ptr to program header offset
	assert(lseek(fd, (off_t) ehdr.e_phoff, SEEK_SET) ==
	       (off_t) ehdr.e_phoff);

    // loop over program header
	for (index = 0; index < ehdr.e_phnum; index++)
	{
        // read program header to phdr64_table
		assert(read(fd, (void *)&phdr64_table, ehdr.e_phentsize) ==
		       ehdr.e_phentsize);

		ph_tbl[index].p_type    = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_type, sizeof(phdr64_table.p_type));
		ph_tbl[index].p_flags   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_flags, sizeof(phdr64_table.p_flags));
		ph_tbl[index].p_offset  = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_offset, sizeof(phdr64_table.p_offset));
		ph_tbl[index].p_vaddr   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_vaddr, sizeof(phdr64_table.p_vaddr));
		ph_tbl[index].p_paddr   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_paddr, sizeof(phdr64_table.p_paddr));
		ph_tbl[index].p_filesz  = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_filesz, sizeof(phdr64_table.p_filesz));
		ph_tbl[index].p_memsz   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_memsz, sizeof(phdr64_table.p_memsz));
		ph_tbl[index].p_flags   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_flags, sizeof(phdr64_table.p_flags));
		ph_tbl[index].p_align   = get_byte_as_little_endian(fifth_magic,
            phdr64_table.p_align, sizeof(phdr64_table.p_align));
	}
}

/**
 * read_elf_program_header - fills the ehdr with suitable(N) architecture
 * data
 * @ehdr: elf header structure
 * @file: input file
 * @arch: architecture of the elf file
 */
void read_elf_program_header(ElfN_Ehdr *ehdr, FILE *file, int arch)
{
	ElfN_Phdr *ph_tbl;
	ElfN_Shdr *sh_tbl;

	if (arch == 64)
		read_elf_header_64(ehdr, file);
	else if (arch == 32)
		read_elf_header_32(ehdr, file);
	
	ph_tbl = malloc(sizeof(ElfN_Phdr) * ehdr->e_phnum);
	sh_tbl = malloc(sizeof(ElfN_Shdr) * ehdr->e_shnum);
	if (!sh_tbl)
		printf("Memory error for section header table :(\n");
	if (!ph_tbl)
		printf("Memory error for program header table :(\n");

	if (arch == 64)
	{
		read_elf_section_header_64(*ehdr, sh_tbl, fileno(file));
		read_elf_program_header_64(*ehdr, ph_tbl, fileno(file));
	}
	else if (arch == 32)
	{
		read_elf_program_header_32(*ehdr, ph_tbl, fileno(file));
		read_elf_section_header_32(*ehdr, sh_tbl, fileno(file));
	}

	print_elf_program_header(ph_tbl, sh_tbl, *ehdr, fileno(file));
}