CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g

_SRC =  0-hreadelf.c \
		validate_elf.c \
		_strlen.c \
		printer_header.c \
		elf_header_utils_0.c \
		elf_header_utils_1.c \
		read_elf_header.c \
		transform_endian.c

_SRC1 = 1-hreadelf.c \
		validate_elf.c \
		_strlen.c \
		elf_header_utils_0.c \
		elf_header_utils_1.c \
		elf_section_utils_0.c \
		read_elf_section.c \
		read_elf_header.c \
		printer_section.c \
		transform_endian.c

_SRC2 = 2-hreadelf.c \
		validate_elf.c \
		utils_0.c \
		utils_1.c \
		utils_2.c \
		process_elf_header.c \
		process_elf_section_header.c \
		process_elf_program_header.c


SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

SRC1 = $(patsubst %,$(SDIR)/%,$(_SRC1))

SRC2 = $(patsubst %,$(SDIR)/%,$(_SRC2))

_OBJ = $(_SRC:.c=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ1 = $(_SRC1:.c=.o)
OBJECTS1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))

_OBJ2 = $(_SRC2:.c=.o)
OBJECTS2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

IDIR = ./inc
SDIR = ./src
ODIR = .

OUTPUT = 0-hreadelf
OUTPUT1 = 1-hreadelf
OUTPUT2 = 2-hreadelf


all : $(OUTPUT1) $(OUTPUT) $(OUTPUT2)

$(OUTPUT) : $(OBJECTS)
	$(CC) -o $@ $^ $(LINKS)

$(OUTPUT1) : $(OBJECTS1)
	$(CC) -o $@ $^ $(LINKS)

$(OUTPUT2) : $(OBJECTS2)
	$(CC) -o $@ $^ $(LINKS)

.PHONY : clean

clean :
	rm -f $(OUTPUT) $(OUTPUT1) $(OBJECTS) $(OBJECTS1) $(OUTPUT2) $(OBJECTS2)

re: $(OBJ) $(OBJ1) $(OBJ2)
