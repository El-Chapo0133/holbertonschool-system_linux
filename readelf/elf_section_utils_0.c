#include "elf_section_utils_0.h"

/**
 * get_section_type_name - gets the section name
 * @sh_type: section type of elf section
 * Return: the section name
 */
char *get_section_type_name(unsigned int sh_type)
{
	static char buff[32];

	switch (sh_type)
	{
        case SHT_NULL:	        return ("NULL");
        case SHT_PROGBITS:		return ("PROGBITS");
        case SHT_SYMTAB:		return ("SYMTAB");
        case SHT_STRTAB:		return ("STRTAB");
        case SHT_RELA:		    return ("RELA");
        case SHT_HASH:		    return ("HASH");
        case SHT_DYNAMIC:		return ("DYNAMIC");
        case SHT_NOTE:		    return ("NOTE");
        case SHT_NOBITS:		return ("NOBITS");
        case SHT_REL:		    return ("REL");
        case SHT_SHLIB:		    return ("SHLIB");
        case SHT_DYNSYM:	    return ("DYNSYM");
        case SHT_INIT_ARRAY:	return ("INIT_ARRAY");
        case SHT_FINI_ARRAY:	return ("FINI_ARRAY");
        case SHT_PREINIT_ARRAY:	return ("PREINIT_ARRAY");
        case SHT_GNU_HASH:		return ("GNU_HASH");
        case SHT_GROUP:		    return ("GROUP");
        case SHT_SYMTAB_SHNDX:	return ("SYMTAB SECTION INDICIES");
        case SHT_GNU_verdef:	return ("VERDEF");
        case SHT_GNU_verneed:	return ("VERNEED");
        case SHT_GNU_versym:	return ("VERSYM");
        case 0x6ffffff0:		return ("VERSYM");
        case 0x6ffffffc:		return ("VERDEF");
        case 0x7ffffffd:		return ("AUXILIARY");
        case 0x7fffffff:		return ("FILTER");
        case SHT_GNU_LIBLIST:	return ("GNU_LIBLIST");
        default:
            /* specific os range */
            if ((sh_type >= SHT_LOOS) && (sh_type <= SHT_HIOS))
                sprintf(buff, "LOOS+%x", sh_type - SHT_LOOS);
            /* specific application range */
            else if ((sh_type >= SHT_LOUSER) && (sh_type <= SHT_HIUSER))
                sprintf(buff, "LOUSER+%x", sh_type - SHT_LOUSER);
            else
                snprintf(buff, sizeof(buff), ("<unknown>: %x"),
                    sh_type);
            return (buff);
	}
}


/**
 * get_elf_section_flags - gets the section flag of elf
 * @elf_header: Elf header
 * @sh_flags: sh_flags of elf section
 * Return: description of flag of section of elf
 */
char *get_elf_section_flags(ElfN_Ehdr elf_header, unsigned long sh_flags)
{
	static char buff[1024];
	char *ptr = buff;
	long flag;

	while (sh_flags)
	{
		flag = sh_flags & -sh_flags;
		sh_flags &= ~flag;
		if (flag == SHF_WRITE)
			*ptr = 'W';
		else if (flag == SHF_ALLOC)
			*ptr = 'A';
		else if (flag == SHF_EXECINSTR)
			*ptr = 'X';
		else if (flag == SHF_MERGE)
			*ptr = 'M';
		else if (flag == SHF_STRINGS)
			*ptr = 'S';
		else if (flag == SHF_INFO_LINK)
			*ptr = 'I';
		else if (flag == SHF_LINK_ORDER)
			*ptr = 'L';
		else if (flag == SHF_OS_NONCONFORMING)
			*ptr = 'O';
		else if (flag == SHF_GROUP)
			*ptr = 'G';
		else if (flag == SHF_TLS)
			*ptr = 'T';
		else if (sh_flags == 0)
			*ptr = 'E';
        else
        {
            if (elf_header.e_machine == EM_X86_64 && flag == 0x10000000)
                *ptr = 'l';
            else if (flag & SHF_MASKOS)
            {
                *ptr = 'o';
                sh_flags &= ~SHF_MASKOS;
            }
            else if (flag & SHF_MASKPROC)
            {
                *ptr = 'p';
                sh_flags &= ~SHF_MASKPROC;
            }
            else
                *ptr = 'x';
        }
		ptr++;
	}
    /* end of buffer null-character */
	*ptr = '\0';
	return (buff);
}