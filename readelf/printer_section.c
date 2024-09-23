#include "printer_section.h"

/**
 * print_flag_detials - display the flag details when section headers are
 * printed
 * @arch32 : if architecture is 32 then true else false
 */
void print_flag_detials(int arch)
{
	printf("Key to Flags:\n");
	if (arch == 32)
		printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	else
		printf("  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");
}

/**
 * print_elf_section_header -  displays the elf header section as
 * "read elf -W -S"
 * @sh_tbl: section header table
 * @fd: file descriptor of input elf file
 * @ehdr: elf header structure
 */
void print_elf_section_header(ElfN_Shdr sh_tbl[], ElfN_Ehdr ehdr, int fd)
{
	int index;
	char *str_tbl;
	int arch = ehdr.e_ident[EI_DATA];

	if (ehdr.e_shnum == 0)
	{
		printf("There are no sections in this file.\n");
		return;
	}
	str_tbl = read_section(fd, sh_tbl[ehdr.e_shstrndx]);
	printf("There are %d section headers, starting at offset 0x%x:\n\n",
	       ehdr.e_shnum, (unsigned int)ehdr.e_shoff);
	printf("Section Headers:\n");
	if (arch == 32)
	{
		printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
	}
	else
	{
		printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");
	}
	for (index = 0; index < ehdr.e_shnum; index++)
	{
		printf("  [%2u] %-17s %-15.15s ", index,
		       str_tbl + sh_tbl[index].sh_name,
		       get_section_type_name(sh_tbl[index].sh_type));
		printf("%0*x %6.6lx %6.6lx %2.2lx", arch == 32 ? 8 : 16,
		       (unsigned int)sh_tbl[index].sh_addr,
		       (unsigned long)sh_tbl[index].sh_offset,
		       (unsigned long)sh_tbl[index].sh_size,
		       (unsigned long)sh_tbl[index].sh_entsize);
		printf(" %3s ", get_elf_section_flags(ehdr, sh_tbl[index].sh_flags));
		printf("%2ld %3lu %2ld\n", (unsigned long)sh_tbl[index].sh_link,
		       (unsigned long)sh_tbl[index].sh_info,
		       (unsigned long)sh_tbl[index].sh_addralign);
	}
	print_flag_detials(arch);
}
