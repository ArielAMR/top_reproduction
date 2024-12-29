##
## EPITECH PROJECT, 2024
## makefile
## File description:
## root makefile
##

CC ?= gcc

SRC = 	src/my_top.c			\
		src/display.c			\
		src/first_line.c		\
		src/second_line.c		\
		src/mem_swap_lines.c	\
		src/display_tasks.c		\
		src/free_list_stat.c	\
		src/strcatpath.c		\
		src/getinstatus.c		\
		src/getinstat.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -iquote include

LIB =  -lncurses

NAME = my_top

all:	cmp

cmp:	$(OBJ)
	gcc -o $(NAME) $(CPPFLAGS) $(CFLAGS) $(OBJ) $(LIB)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean cmp crlib
