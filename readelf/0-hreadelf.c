#include "readelf.h"

/**
 * main - This is the main function
 * @argc: this is argc
 * @argv: this is argv
 *
 * Return: normal main return
 */
int main(int argc, char *argv[])
{
	ElfN_Ehdr ehdr;
	int exit_status = 0, arch = 0;
	FILE *file;

	/* validate user input */
	if (argc < 2)
	{
		printf("You must provide an ELF file :(\n");
		exit(1);
	}
	/* open the elf file */
	file = fopen(argv[1], "rb");
	if (file)
	{
		if (fread(ehdr.e_ident, EI_NIDENT, 1, file) &&
		    elf_check_file(ehdr.e_ident))
		{
			get_architecture(ehdr.e_ident[EI_CLASS], &arch);
			if (arch == 64)
			{
				read_elf_header_64(&ehdr, file);
			} else if (arch == 32)
			{
				read_elf_header_32(&ehdr, file);
			}
			print_elf_header(ehdr);
		} else
			printf("%s: %s\n", E, argv[0]);
		exit_status = 1;
		/* finally close the file */
		fclose(file);
	}
	else
	{
		printf("%s: Error: '%s': No such file\n", argv[0], argv[1]);
		exit_status = 1;
	}
	return (exit_status);
}
