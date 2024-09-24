#include "elf_program_header_utils.h"

/**
 * get_segment_type - gets the segment type  of elf
 * @p_type: p_type of elf program header
 * Return: description of segment type of elf program header
 */
char *get_segment_type(unsigned long p_type)
{
	static char buff[32];

	switch (p_type)
	{
        case PT_NULL:
            return ("NULL");
        case PT_LOAD:
            return ("LOAD");
        case PT_DYNAMIC:
            return ("DYNAMIC");
        case PT_INTERP:
            return ("INTERP");
        case PT_NOTE:
            return ("NOTE");
        case PT_SHLIB:
            return ("SHLIB");
        case PT_PHDR:
            return ("PHDR");
        case PT_TLS:
            return ("TLS");
        case PT_GNU_EH_FRAME:
            return ("GNU_EH_FRAME");
        case PT_GNU_STACK:
            return ("GNU_STACK");
        case PT_GNU_RELRO:
            return ("GNU_RELRO");

        default:
            if ((p_type >= PT_LOPROC) && (p_type <= PT_HIPROC))
            {
                sprintf(buff, "LOPROC+%lx", p_type - PT_LOPROC);
            } else if ((p_type >= PT_LOOS) && (p_type <= PT_HIOS))
            {
                sprintf(buff, "LOOS+%lx", p_type - PT_LOOS);
            } else
                snprintf(buff, sizeof(buff), ("<unknown>: %lx"),
                    p_type);
            return (buff);
	}
}