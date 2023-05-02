##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile for my_ftp
##

SRC	=	src/my_str_to_word_array.c	\
		src/str_utils.c	\
		src/error_handling.c 	\
		src/client_utils.c	\
		src/client_quit.c	\
		src/client_login.c 	\
		src/client_command_parser.c	\
		src/server_main_thread.c	\
		src/socket_utils.c	\
		src/passive_server.c	\
		src/file_ops.c	\
		src/client_help.c	\
		src/active_server.c	\
		src/file_storing.c	\
		src/client_working_directories.c	\
		src/list_files_main.c	\
		src/str_ops.c	\
		src/directory_listing.c	\
		src/reset_sockets.c	\
		src/port_utils.c	\
		main.c

OBJ	=	$(SRC:.c=.o)

CPPFLAGS	=	-Iinclude/

CCRITERION	= 	--coverage -lcriterion

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all re clean tests_run fclean
