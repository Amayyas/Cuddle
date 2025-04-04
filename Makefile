##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

AR = ar rc
INCLUDE_DIR = ./include
CPPFLAGS = -I $(INCLUDE_DIR)
CFLAGS = -Wall -Wextra -W -g3 -lm
NAME = libcuddle.a
SRC_DIR = ./src
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) vgcore.*

re: fclean all

test: all
	gcc -o test Stuff/main.c libcuddle.a -I ./include -lm
	valgrind --leak-check=full ./test

direct_test: all
	gcc -o test Stuff/main.c libcuddle.a -I ./include -lm
	./test
