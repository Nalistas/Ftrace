##
## EPITECH PROJECT, 2022
## makefile
## File description:
## Makefile
##

CC		=	 	gcc
SRC		=		src/main.c	\
				src/launch_ftrace.c	\
				src/execve_case.c	\
				src/call_stack/ftrace_call_stack.c	\
				src/display_detailed/display.c	\
				src/display_detailed/display_fct/default_display.c	\
				src/display_detailed/display_fct/string_display.c	\
				src/display_detailed/display_fct/sized_ptr_display.c	\
				src/process_file/init_process_library.c	\
				src/process_file/process_lib_utils.c	\
				src/check_call/check_call.c	\
				src/check_call/check_e8.c	\
				src/process_file/find_symbol.c	\
				src/process_file/get_fct_name.c	\
				src/check_call/check_ff.c	\
				src/call_stack/graph_stack_base.c	\
				src/call_stack/graph_stack_manip.c	\

NAME		=	ftrace

CPPFLAGS	=	-Wextra -Wall -W -g3
CPPFLAGS	+=	-iquote include/ -iquote lib/include/
CPPFLAGS	+=	-lmyelf -L./lib

# CFLAGS		=	 	-g3

OBJ		=		$(SRC:.c=.o)

all:	$(NAME)
$(NAME):	$(OBJ)
	make -C ./lib
	@$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	make -C ./lib clean
	@$(RM) $(OBJ)
	@$(RM) *.gcda
	@$(RM) *.gcno

fclean: clean
	make -C ./lib fclean
	@$(RM) $(NAME)
	@$(RM) $(UT_NAME)


re: fclean all

.PHONY: re fclean clean all
