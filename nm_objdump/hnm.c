#include "hnm.h"





ElfN_Ehdr process_header(int fd, char *file_name)
{
	size_t byte_read;
	ElfN_Ehdr ehdr;

	byte_read = read(fd, ehdr.e_ident, EI_NIDENT);

	if (byte_read != 0 && elf_check_file(ehdr.e_ident))
	{
		fprintf(stderr, "hnm: %s: File format not recognized\n", file_name);
		return (NULL);
	}
	arch = get_architechture(ehdr.e_ident[EI_CLASS]);
	if (arch == -1)
	{
		fprintf(stderr, "%s - %s\n", ERROR_ELF_FILE, file_name);
		return (NULL);
	}

	return (ehdr);
}

int fill_e_ident_and_validate_elf(int fd, ElfN_ehdr *ehdr)
{
	int arch;
	size_t byte_read;

	byte_read = read(fd, (*ehdr).e_ident, EI_NIDENT);

	if (byte_read != 0 && elf_check_file((*ehdr).e_ident))
	{
		fprintf(stderr, "hnm: %s: File format not recognized\n", file_name);
		return (false);
	}
	arch = get_architechture((*ehdr).e_ident[EI_CLASS]);
	if (arch == -1)
	{
		fprintf(stderr, "%s - %s\n", ERROR_ELF_FILE, file_name);
		return (false);
	}

	return (true);
}

int open_file(char *file_address)
{
	int fd;
	struct stat fstat;

	stat(file_address, &fstat);

	if (S_ISDIR(fstat.st_mode)) /* given file is a directory */
	{
		fprintf(stderr, "hnm: Warning: '%s' is a directory\n", file_address);
		return (-1);
	}

	fd = open(file_address, O_RDONLY);
	if (!fd) /* ohoh not good */
	{
		fprintf(stderr, "hnm: '%s': No such file", file_address);
		return (-1);
	}
	return (fd);
}

int main(int argc, char **argv)
{
	int fd, arch, flag, index = 1, exit_code = EXIT_SUCCESS;
	ElfN_Ehdr ehdr;
	ElfN_Shdr shdr;

	do
	{
		if (argc == 1)
			argv[index] = "a.out";

		fd = open_file(argv[index]);
		if (fd == -1)
			return (EXIT_FAILURE);

		if (!fill_e_ident_and_validate_elf(fd, &ehdr))
		{
			fprintf(stderr, "ELF is incorrect");
			return (EXIT_FAILURE);
		}

		ehdr = process_header(fd, argv[index]);

		index++;
	}
	while (index < argc);

	return (exit_code);
}
