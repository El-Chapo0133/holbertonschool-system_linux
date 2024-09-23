#include "printer_header.h"


/**
 * print_elf_header - displays the elf header section as "read elf -W -h"
 * @ehdr: elf header structure
 */
void print_elf_header(ElfN_Ehdr ehdr)
{
    print_magic_number(ehdr);
	print_all_attributes(ehdr);
}

void print_magic_number(ElfN_Ehdr ehdr)
{
    int index;

	printf("ELF Header:\n  Magic:   ");
	for (index = 0; index < 16; index++)
	{
		printf("%02x ", ehdr.e_ident[index]);
		if (index == 15)
			printf("\n");
	}
}
void print_all_attributes(ElfN_Ehdr ehdr)
{
    int index;
	Entry entries[18];

	flatten_elf_header(ehdr, entries);
	for (index = 0; index < 18; index++)
	{
        /* print key + correct amount of space + value */
		printf("  %s:%*s%s\n", entries[index].key,
		       34 - (int)_strlen(entries[index].key), "", entries[index].value);
	}
}


/**
 * read_elf_header - fills the elf header info
 * @ehdr: elf header structure
 * @entries: elf header info filled in key and values
 */
void flatten_elf_header(ElfN_Ehdr ehdr, Entry entries[])
{
	/* Most absurd way to fill the entries but no other way */
	entries[0].key = strdup("Class");
	entries[0].value = get_elf_class(ehdr.e_ident[EI_CLASS]);
	entries[1].key = strdup("Data");
	entries[1].value = get_data_encoding(ehdr.e_ident[EI_DATA]);
	entries[2].key = strdup("Version");
	entries[2].value = get_elf_version(ehdr.e_ident[EI_VERSION]);
	entries[3].key = strdup("OS/ABI");
	entries[3].value = get_osabi_name(ehdr.e_ident[EI_OSABI]);
	entries[4].key = strdup("ABI Version");
	entries[4].value = get_vma(ehdr.e_ident[EI_ABIVERSION], 'd', '0');
	entries[5].key = strdup("Type");
	entries[5].value = get_file_type(ehdr.e_type);
	entries[6].key = strdup("Machine");
	entries[6].value = get_machine_name(ehdr.e_machine);
	entries[7].key = strdup("Version");
	entries[7].value = get_vma(ehdr.e_version, 'x', '0');
	entries[8].key = strdup("Entry point address");
	entries[8].value = get_vma(ehdr.e_entry, 'x', '0');
	entries[9].key = strdup("Start of program headers");
	entries[9].value = get_vma(ehdr.e_phoff, 'd', 'f');
	entries[10].key = strdup("Start of section headers");
	entries[10].value = get_vma(ehdr.e_shoff, 'd', 'f');
	entries[11].key = strdup("Flags");
	entries[11].value = get_vma(ehdr.e_flags, 'x', '0');
	entries[12].key = strdup("Size of this header");
	entries[12].value = get_vma(ehdr.e_ehsize, 'd', 'b');
	entries[13].key = strdup("Size of program headers");
	entries[13].value = get_vma(ehdr.e_phentsize, 'd', 'b');
	entries[14].key = strdup("Number of program headers");
	entries[14].value = get_vma(ehdr.e_phnum, 'd', '0');
	entries[15].key = strdup("Size of section headers");
	entries[15].value = get_vma(ehdr.e_shentsize, 'd', 'b');
	entries[16].key = strdup("Number of section headers");
	entries[16].value = get_vma(ehdr.e_shnum, 'd', '0');
	entries[17].key = strdup("Section header string table index");
	entries[17].value = get_vma(ehdr.e_shstrndx, 'd', '0');
}