CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

OBJ = $(wildcard *.c)
HEADERS = $(wildcard *.h)

NAME = hnm

# Main directive
all: $(NAME)

# Compile executable from object files
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean, run, memcheck, memfull

clean:
	rm -f *.o $(NAME)

run: all
	@./$(NAME)

memcheck: all
	@valgrind ./$(NAME)

memfull: all
	@valgrind --leak-check=full --track-origins=yes ./$(NAME)

crun: clean, all
	@./$(NAME)
