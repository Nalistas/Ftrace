##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile elffile lib
##

SRC	=	src/interface/myelf_manager.c	\
		src/interface/myelf_request.c	\
		src/interface/myelf_iterator_create.c	\
		src/interface/myelf_iterator_manager.c	\
		src/interface/myelf_basic_data_getter.c	\
		src/interface/myelf_get_tab.c	\
		src/interface/myelf_get_existant_elf.c	\
\
\
		src/elffile/elffile.c	\
		src/elffile/b32/get_ehdr_data32.c	\
		src/elffile/b32/get_info_program32.c	\
		src/elffile/b32/get_shdr_data32.c	\
		src/elffile/b32/init_elf32.c	\
		src/elffile/b32/symtab32.c	\
		src/elffile/b32/get_phdr_data32.c	\
		src/elffile/b32/get_sym_data32.c	\
		src/elffile/b32/create_iter32.c	\
\
\
		src/elffile/b64/get_ehdr_data64.c	\
		src/elffile/b64/get_info_program64.c	\
		src/elffile/b64/get_shdr_data64.c	\
		src/elffile/b64/init_elf64.c	\
		src/elffile/b64/symtab64.c	\
		src/elffile/b64/get_phdr_data64.c	\
		src/elffile/b64/get_sym_data64.c	\
		src/elffile/b64/create_iter64.c	\

CPPFLAGS	=	-Wall -Wextra -Werror -I./include -g3

OBJ	=	$(SRC:.c=.o)

NAME	=	libmyelf.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all re fclean clean
