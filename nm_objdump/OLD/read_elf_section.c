#include "read_elf_section.h"

/**
 * read_elf_section_header_32- fills the sh with suitable(32)
 * architecture data
 * @sh_tbl: section header table
 * @fd: file descriptor of input elf file
 * @ehdr: elf header structure
 */
void read_elf_section_header_32(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd)
{
	int index;
	Elf32_Shdr shdr32_table;
	unsigned char magic_endian = ehdr.e_ident[EI_DATA]; // either 1 or 2

	/* seek to the section memory */
	assert(lseek(fd, (off_t) ehdr.e_shoff, SEEK_SET) == (off_t) ehdr.e_shoff);

	for (index = 0; index < ehdr.e_shnum; index++)
	{
		/* read the section table to shdr32_table, and ensure it has the right size */
		/* ehdr.e_shentsize is the "section header size" */
		assert(read(fd, (void *)&shdr32_table, ehdr.e_shentsize) == ehdr.e_shentsize);

		/* fill the section header table */
		sh_tbl[index].sh_name 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_name, sizeof(shdr32_table.sh_name));
		sh_tbl[index].sh_type 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_type, sizeof(shdr32_table.sh_type));
		sh_tbl[index].sh_flags 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_flags, sizeof(shdr32_table.sh_flags));
		sh_tbl[index].sh_addr 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_addr, sizeof(shdr32_table.sh_addr));
		sh_tbl[index].sh_offset 	= get_byte_as_little_endian(magic_endian, shdr32_table.sh_offset, sizeof(shdr32_table.sh_offset));
		sh_tbl[index].sh_size 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_size, sizeof(shdr32_table.sh_size));
		sh_tbl[index].sh_link 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_link, sizeof(shdr32_table.sh_link));
		sh_tbl[index].sh_info 		= get_byte_as_little_endian(magic_endian, shdr32_table.sh_info, sizeof(shdr32_table.sh_info));
		sh_tbl[index].sh_addralign 	= get_byte_as_little_endian(magic_endian, shdr32_table.sh_addralign, sizeof(shdr32_table.sh_addralign));
		sh_tbl[index].sh_entsize 	= get_byte_as_little_endian(magic_endian, shdr32_table.sh_entsize, sizeof(shdr32_table.sh_entsize));
	}
}

/**
 * read_elf_section_header_64- fills the sh with suitable(64)
 * architecture data
 * @sh_tbl: section header table
 * @fd: file descriptor of input elf file
 * @ehdr: elf header structure
 */
void read_elf_section_header_64(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd)
{
	int index;
	Elf64_Shdr shdr64_table;
	unsigned char magic_endian = ehdr.e_ident[EI_DATA]; // either 1 or 2

	/* seek to the section memory */
	assert(lseek(fd, (off_t) ehdr.e_shoff, SEEK_SET) == (off_t) ehdr.e_shoff);

	for (index = 0; index < ehdr.e_shnum; index++)
	{
		/* read the section table to shdr64_table, and ensure it has the right size */
		/* ehdr.e_shentsize is the "section header size" */
		assert(read(fd, (void *)&shdr64_table, ehdr.e_shentsize) == ehdr.e_shentsize);

		/* fill the section header table */
		sh_tbl[index].sh_name 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_name, sizeof(shdr64_table.sh_name));
		sh_tbl[index].sh_type 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_type, sizeof(shdr64_table.sh_type));
		sh_tbl[index].sh_flags 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_flags, sizeof(shdr64_table.sh_flags));
		sh_tbl[index].sh_addr 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_addr, sizeof(shdr64_table.sh_addr));
		sh_tbl[index].sh_offset 	= get_byte_as_little_endian(magic_endian, shdr64_table.sh_offset, sizeof(shdr64_table.sh_offset));
		sh_tbl[index].sh_size 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_size, sizeof(shdr64_table.sh_size));
		sh_tbl[index].sh_link 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_link, sizeof(shdr64_table.sh_link));
		sh_tbl[index].sh_info 		= get_byte_as_little_endian(magic_endian, shdr64_table.sh_info, sizeof(shdr64_table.sh_info));
		sh_tbl[index].sh_addralign 	= get_byte_as_little_endian(magic_endian, shdr64_table.sh_addralign, sizeof(shdr64_table.sh_addralign));
		sh_tbl[index].sh_entsize 	= get_byte_as_little_endian(magic_endian, shdr64_table.sh_entsize, sizeof(shdr64_table.sh_entsize));
	}
}

/**
 * read_elf_section_header - fills the ehdr with suitable(N) architecture
 * and print the sections
 * @ehdr: elf header structure
 * @file: input file
 * @arch: architecture of the elf file
 */
void read_elf_section_header(ElfN_Ehdr *ehdr, FILE *file, int arch)
{
	ElfN_Shdr *section_header_table;

	/* headers are needed to know the locations of the sections */
	if (arch == 32)
		read_elf_header_32(ehdr, file);
	else if (arch == 64)
		read_elf_header_64(ehdr, file);
	
	section_header_table = malloc(sizeof(ElfN_Shdr) * ehdr->e_shnum);
	if (!section_header_table)
		printf("Failed to allocate section header table\n");

	/* read all the sections */
	if (arch == 32)
		read_elf_section_header_32(*ehdr, section_header_table, fileno(file));
	else if (arch == 64)
		read_elf_section_header_64(*ehdr, section_header_table, fileno(file));

	/* print all the sections */
	print_elf_section_header(section_header_table, *ehdr, fileno(file));
}


/**
 * read_section - seek to the start of the section and read the section
 * @sh: section header
 * @fd: file descriptor of input elf file
 * Return: string representation of the file
 */
char *read_section(int fd, ElfN_Shdr sh)
{
	char *buff = malloc(sh.sh_size + 1);

	if (buff == NULL)
	{
		printf("Memory error :(\n");
		return (NULL);
	}

	/* read the specific section */
	assert(lseek(fd, (off_t)sh.sh_offset, SEEK_SET) == (off_t)sh.sh_offset);
	assert(read(fd, (void *)buff, sh.sh_size) == (ssize_t)sh.sh_size);

	/* end of section null-character */
	buff[sh.sh_size] = '\0';
	return (buff);
}