#include "printer_program_header.h"

/**
 * print_header - display the file details  & header
 * @ehdr : elf header
 * @arch32 : if architecture is 32 then true else false
 */
void print_header(ElfN_Ehdr ehdr, bool arch32)
{
	printf("\nElf file type is %s\n", get_file_type(ehdr.e_type));
	printf("Entry point 0x%x\n", (unsigned int)ehdr.e_entry);
	printf("There are %d program headers, starting at offset %d\n\n",
	       ehdr.e_phnum, (unsigned int)ehdr.e_phoff);
	printf("Program Headers:\n");
	if (arch32)
	{
		printf("  Type           Offset   VirtAddr   PhysAddr   ");
		printf("FileSiz MemSiz  Flg Align\n");
	}
	else
	{
		printf("  Type           Offset   VirtAddr           PhysAddr      ");
		printf("     FileSiz  MemSiz   Flg Align\n");
	}
}
/**
 * print_type_header - display the additional details for the type
 * @ph_tbl : segment
 * @fd : file descriptor of the input elf file
 */
void print_type_header(ElfN_Phdr ph_tbl, int fd)
{
	char fmt[32], program_interpreter[PATH_MAX];

	switch (ph_tbl.p_type)
	{
		case PT_INTERP:
		if (lseek(fd, ph_tbl.p_offset, SEEK_SET) != ph_tbl.p_offset)
			printf("Unable to find program interpreter name\n");
		else
		{
			int ret = snprintf(fmt, sizeof(fmt), "%%%ds", PATH_MAX - 1);

			if (ret >= (int)sizeof(fmt) || ret < 0)
			{
				printf("Internal error: failed to create format string to display ");
				printf("program interpreter\n");
			}
			program_interpreter[0] = 0;
			if (read(fd, program_interpreter, sizeof(fmt)) <= 0)
				printf("Unable to read program interpreter name\n");
			else
				printf("      [Requesting program interpreter: %s]\n",
						 program_interpreter);
		}
		break;
	}
}
/**
 * print_elf_program_header -  displays the elf header program as
 * "read elf -W -P"
 * @ph_tbl: program header table
 * @sh_tbl: section header table
 * @file: input elf file
 * @ehdr: elf header structure
 */
void print_elf_program_header(ElfN_Phdr ph_tbl[], ElfN_Shdr sh_tbl[],
			      ElfN_Ehdr ehdr, int fd)
{
	int i = 0, j = 0;
	char *str_tbl = read_section(fd, sh_tbl[ehdr.e_shstrndx]);
	bool arch32 = ehdr.e_ident[EI_CLASS] == ELFCLASS32;

	if (ehdr.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}
	print_header(ehdr, arch32);
	for (i = 0; i < ehdr.e_phnum; i++)
	{
		printf("  %-14s ", get_segment_type(ph_tbl[i].p_type));
		printf("0x%6.6lx ", (unsigned long)ph_tbl[i].p_offset);
		printf("0x%*.*lx ", (arch32) ? 8 : 16, (arch32) ? 8 : 16,
		       (unsigned long)ph_tbl[i].p_vaddr);
		printf("0x%*.*lx ", (arch32) ? 8 : 16, (arch32) ? 8 : 16,
		       (unsigned long)ph_tbl[i].p_paddr);
		printf("0x%*.*lx ", (arch32) ? 5 : 6, (arch32) ? 5 : 6,
		       (unsigned long)ph_tbl[i].p_filesz);
		printf("0x%*.*lx ", (arch32) ? 5 : 6, (arch32) ? 5 : 6,
		       (unsigned long)ph_tbl[i].p_memsz);
		printf("%c%c%c ", (ph_tbl[i].p_flags & PF_R ? 'R' : ' '),
		       (ph_tbl[i].p_flags & PF_W ? 'W' : ' '),
		       (ph_tbl[i].p_flags & PF_X ? 'E' : ' '));
		printf("%#lx\n", (unsigned long)ph_tbl[i].p_align);
		print_type_header(ph_tbl[i], fd);
	}
	printf("\n Section to Segment mapping:\n");
	printf("  Segment Sections...\n");
	for (i = 0; i < ehdr.e_phnum; i++)
	{
		printf("   %2.2d     ", i);
		for (j = 0; j < ehdr.e_shnum && str_tbl; j++)
			if (ELF_IS_SECTION_IN_SEGMENT(sh_tbl[j], ph_tbl[i])
			    && sh_tbl[j].sh_size)
				printf("%s ", str_tbl + sh_tbl[j].sh_name);
		putc('\n', stdout);
	}
}