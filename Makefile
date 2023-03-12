##
## EPITECH PROJECT, 2023
## FTP [WSL: Ubuntu]
## File description:
## Makefile
##

SRC			=	src/main.c				\
				src/binary_arguments.c	\
				src/commands.c			\
				src/file_actions.c		\
				src/file_transfer.c		\
				src/help.c				\
				src/path_actions.c 		\
				src/response.c			\
				src/server_execution.c	\
				src/server_struct.c		\
				src/user.c				\
				src/signal.c

OBJ			=	$(SRC:.c=.o)

NAME		=	myftp

CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I./include

DEBUG_FLAG	=	-g

CC			=	gcc

RM 			=	rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(INCLUDE)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

debug:	CFLAGS += $(DEBUG_FLAG)
debug:	re

.PHONY:	all clean fclean re debug
