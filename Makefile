NAME = libasm.a
TEST_NAME = tests

NASM = nasm
NASMFLAGS = -f elf64

CC = cc
CFLAGS = -Wall -Wextra

RM = rm -f

ASM_SRC = $(wildcard srcs/*.s)
ASM_OBJ = $(ASM_SRC:.s=.o)

all: $(NAME) $(TEST_NAME)

$(NAME): $(ASM_OBJ)
	ar rcs $(NAME) $(ASM_OBJ)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(TEST_NAME): test.o
	$(CC) $(CFLAGS) test.o -L. -lasm -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

clean:
	$(RM) $(ASM_OBJ) test.o

fclean: clean
	$(RM) $(NAME) test

re: fclean all

.PHONY: all test clean fclean re