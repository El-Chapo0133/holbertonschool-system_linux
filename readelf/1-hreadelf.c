#include "1-hreadelf.h"

/**
 * main - A program that takes the name of a elf file as a parameter and
 * displays the information contained in section headers of an  ELF file.
 * @argc: no of inputs.
 * @argv: inputs.
 *
 * Return: on success:  0 , on Failure: 1.
 */
int main(int argc, char *argv[])
{
	ElfN_Ehdr ehdr;
	int exit_status = 0, arch = 0;
	FILE *file;

	/* validate user input */
	if (argc < 2)
	{
		printf("Usage: %s elf_filename\n", argv[0]);
		exit(1);
	}
	
	/* open the elf file */
	file = fopen(argv[1], "rb");
	if (!file)
	{
		printf("%s: Error: '%s': No such file\n", argv[0], argv[1]);
		exit(1);
	}
	if (fread(ehdr.e_ident, EI_NIDENT, 1, file) && elf_check_file(ehdr.e_ident))
	{
		arch = get_architecture(ehdr.e_ident[EI_CLASS]);
        if (arch == -1)
        {
            printf("%s: %s\n", ERROR_ELF_FILE, argv[0]);
            exit_status = 1;
        }
        else
        {
		    read_elf_section_header(&ehdr, file, arch);
        }
	}
	else
	{
		printf("%s: %s\n", ERROR_ELF_FILE, argv[0]);
		exit_status = 1;
	}
	/* finally close the file */
	fclose(file);
	
	return (exit_status);
}