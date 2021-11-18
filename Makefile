MAKEFLAGS	+=	--quiet

WHT	= \033[0;37m
BLK	= \033[0;30m
RED	= \033[0;31m
YEL	= \033[0;33m
BLU	= \033[0;34m
GRN	= \033[0;32m

NAME	=	minishell

HEADERS	=	includes

DIR_S	=	srcs

DIR_O	=	obj

# Using wildcards: $(shell find $(DIR_S) -name *.c)
SRCS 		:=	srcs/main.c \
				srcs/commands/ft_cd.c \
				srcs/commands/ft_pwd.c \
				srcs/executing/find_path.c \
				srcs/executing/run_command.c \
				srcs/redirecting/change_in.c \
				srcs/redirecting/change_out.c \
				srcs/redirecting/fd_closer.c \
				srcs/redirecting/get_fd.c \
				srcs/redirecting/set_in_and_out.c \
				srcs/redirecting/set_pipes.c \
				srcs/utils/ft_split.c \
				srcs/utils/ft_strcmp.c \
				srcs/utils/print_error.c \
				srcs/utils/ft_append.c \
				srcs/utils/ft_putstr_fd.c \
				srcs/gnl/get_next_line.c \
				srcs/reader/get_line.c \
				srcs/parser/parser.c \
				srcs/cleaning/clean_shell.c \

OBJS		:= $(SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%)

# Using wildcards: $(shell find $(HEADERS) -name *.h)
DEPS	=	includes/commands.h \
			includes/executing.h \
			includes/redirecting.h \
			includes/utils.h \
			includes/get_next_line.h \
			includes/reader.h \
			includes/parser.h \
			includes/cleaning.h \
			includes/structures.h \
			includes/minishell.h \

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -pthread

INCLUDES	= -I $(HEADERS)

LIBS	=	-lreadline	

RM		=	rm -f

$(DIR_O)/%.o: %.c
			@mkdir -p $(DIR_O)
			@mkdir -p $(SUB_DIR_O)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME):	$(DEPS) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
			printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			$(RM) $(BONUS_OBJS)
			printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"

fclean:		clean
			$(RM) $(NAME)
			printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"

re:			fclean all

.PHONY:		all clean fclean re			
