#include "hnm.h"





int process_nm(int fd, char *file_name)
{
	size_t byte_read;
	elf_header_all_t *helf;
	ElfN_Ehdr ehdr;

	memset(&helf, 0, 8);
	
	byte_read = read(fd, ehdr.e_ident, EI_NIDENT);
	printf("%s\n", ehdr.e_ident);
	if (byte_read != 0 && elf_check_file(ehdr.e_ident))
	{
		printf("foo\n");
		printf("%c - %s\n", ehdr.e_ident[EI_CLASS], file_name);
	}
	printf("foo\n");
	
	/*
	byte_read = read(fd, &helf->ehdr, sizeof(helf->ehdr));
	if(byte_read != sizeof(helf->ehdr))
	{
		fprintf(stderr, "hnm, %s: File format not recognised\n", file_name);
		return (EXIT_FAILURE);
	}
	
	byte_read = read(fd, &helf->ehdr32, sizeof(helf->ehdr));
	*/
	return (1);
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
	int fd, index = 1, exit_code = EXIT_SUCCESS;

	do	
	{
		if (argc == 1)
			argv[index] = "a.out";

		fd = open_file(argv[index]);
		if (fd == -1)
			return (EXIT_FAILURE);
		
		process_nm(fd, argv[index]);
		
		index++;
	}
	while (index < argc);

	return (exit_code);
}
