/**
 * read_elf_header_32 -  fills the ehdr with suitable(32) architecture data
 * @ehdr: elf header structure
 * @file: input file
 */
void read_elf_header_32(ElfN_Ehdr *ehdr, FILE *file)
{
	ssize_t byte_read;
	unsigned char magic_endian = ehdr->e_ident[EI_DATA];
	Elf32_Ehdr ehdr32;

	byte_read = fread(&ehdr32.e_type, sizeof(ehdr32) - EI_NIDENT, 1, file);
	if (byte_read != 1)
		exit(EXIT_FAILURE);

	ehdr->e_type 		= get_byte_as_little_endian(magic_endian, ehdr32.e_type, sizeof(ehdr32.e_type));
	ehdr->e_machine 	= get_byte_as_little_endian(magic_endian, ehdr32.e_machine, sizeof(ehdr32.e_machine));
	ehdr->e_version 	= get_byte_as_little_endian(magic_endian, ehdr32.e_version, sizeof(ehdr32.e_version));
	ehdr->e_entry 		= get_byte_as_little_endian(magic_endian, ehdr32.e_entry, sizeof(ehdr32.e_entry));
	ehdr->e_phoff 		= get_byte_as_little_endian(magic_endian, ehdr32.e_phoff, sizeof(ehdr32.e_phoff));
	ehdr->e_shoff 		= get_byte_as_little_endian(magic_endian, ehdr32.e_shoff, sizeof(ehdr32.e_shoff));
	ehdr->e_flags 		= get_byte_as_little_endian(magic_endian, ehdr32.e_flags, sizeof(ehdr32.e_flags));
	ehdr->e_ehsize 		= get_byte_as_little_endian(magic_endian, ehdr32.e_ehsize, sizeof(ehdr32.e_ehsize));
	ehdr->e_phentsize 	= get_byte_as_little_endian(magic_endian, ehdr32.e_phentsize, sizeof(ehdr32.e_phentsize));
	ehdr->e_phnum 		= get_byte_as_little_endian(magic_endian, ehdr32.e_phnum, sizeof(ehdr32.e_phnum));
	ehdr->e_shentsize 	= get_byte_as_little_endian(magic_endian, ehdr32.e_shentsize, sizeof(ehdr32.e_shentsize));
	ehdr->e_shnum 		= get_byte_as_little_endian(magic_endian, ehdr32.e_shnum, sizeof(ehdr32.e_shnum));
	ehdr->e_shstrndx 	= get_byte_as_little_endian(magic_endian, ehdr32.e_shstrndx, sizeof(ehdr32.e_shstrndx));
}

/**
 * read_elf_header_64 -  fills the ehdr with suitable(64) architecture data
 * @ehdr: elf header structure
 * @file: input file
 */
void read_elf_header_64(ElfN_Ehdr *ehdr, FILE *file)
{
	ssize_t byte_read;
	unsigned char magic_endian = ehdr->e_ident[EI_DATA];
	Elf64_Ehdr ehdr64;

	byte_read = fread(&ehdr64.e_type, sizeof(ehdr64) - EI_NIDENT, 1, file);
	if (byte_read != 1)
		exit(EXIT_FAILURE);

	ehdr->e_type 		= get_byte_as_little_endian(magic_endian, ehdr64.e_type, sizeof(ehdr64.e_type));
	ehdr->e_machine 	= get_byte_as_little_endian(magic_endian, ehdr64.e_machine, sizeof(ehdr64.e_machine));
	ehdr->e_version 	= get_byte_as_little_endian(magic_endian, ehdr64.e_version, sizeof(ehdr64.e_version));
	ehdr->e_entry 		= get_byte_as_little_endian(magic_endian, ehdr64.e_entry, sizeof(ehdr64.e_entry));
	ehdr->e_phoff 		= get_byte_as_little_endian(magic_endian, ehdr64.e_phoff, sizeof(ehdr64.e_phoff));
	ehdr->e_shoff 		= get_byte_as_little_endian(magic_endian, ehdr64.e_shoff, sizeof(ehdr64.e_shoff));
	ehdr->e_flags 		= get_byte_as_little_endian(magic_endian, ehdr64.e_flags, sizeof(ehdr64.e_flags));
	ehdr->e_ehsize 		= get_byte_as_little_endian(magic_endian, ehdr64.e_ehsize, sizeof(ehdr64.e_ehsize));
	ehdr->e_phentsize 	= get_byte_as_little_endian(magic_endian, ehdr64.e_phentsize, sizeof(ehdr64.e_phentsize));
	ehdr->e_phnum 		= get_byte_as_little_endian(magic_endian, ehdr64.e_phnum, sizeof(ehdr64.e_phnum));
	ehdr->e_shentsize 	= get_byte_as_little_endian(magic_endian, ehdr64.e_shentsize, sizeof(ehdr64.e_shentsize));
	ehdr->e_shnum 		= get_byte_as_little_endian(magic_endian, ehdr64.e_shnum, sizeof(ehdr64.e_shnum));
	ehdr->e_shstrndx 	= get_byte_as_little_endian(magic_endian, ehdr64.e_shstrndx, sizeof(ehdr64.e_shstrndx));
}