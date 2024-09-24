#ifndef ELFN_PHDR
#define ELFN_PHDR

/**
 * struct phdr - Struct to represent program headers from both 32 and 64bits
 * @p_type :  Identifies program segment type
 * @p_offset : Segment file offset
 * @p_vaddr : Segment virtual address
 * @p_paddr : Segment physical address
 * @p_filesz : Segment size in file
 * @p_memsz : Segment size in memory
 * @p_flags : Segment flags
 * @p_align : Segment alignment, file & memory
 */
typedef struct phdr
{
	uint32_t p_type;
	uint32_t p_offset;
	uint64_t p_vaddr;
	uint64_t p_paddr;
	uint64_t p_filesz;
	uint64_t p_memsz;
	uint64_t p_flags;
	uint64_t p_align;
} ElfN_Phdr;

#endif