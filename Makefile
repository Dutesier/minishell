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
	\
				srcs/commands/ft_cd.c \
				srcs/commands/ft_pwd.c \
				srcs/commands/ft_echo.c \
				srcs/commands/ft_env.c \
				srcs/commands/ft_export.c \
				srcs/commands/ft_unset.c \
				srcs/commands/ft_envp.c \
				srcs/commands/ft_exit.c \
	\
				srcs/executing/find_path.c \
				srcs/executing/run_command.c \
				srcs/executing/init_command.c \
				srcs/executing/init_command_utils.c \
				srcs/executing/ast_handler.c \
				srcs/executing/command_table.c \
				srcs/executing/set_variables.c \
				srcs/executing/variable_expansion.c \
				srcs/executing/variables.c \
	\
				srcs/redirecting/change_in.c \
				srcs/redirecting/change_out.c \
				srcs/redirecting/fd_closer.c \
				srcs/redirecting/get_fd.c \
				srcs/redirecting/set_in_and_out.c \
				srcs/redirecting/set_pipes.c \
				srcs/redirecting/ft_heredoc.c \
	\
				srcs/utils/ft_split.c \
				srcs/utils/ft_strcmp.c \
				srcs/utils/print_error.c \
				srcs/utils/ft_append.c \
				srcs/utils/ft_putstr_fd.c \
				srcs/utils/ft_strings.c \
				srcs/utils/get_quote.c \
				srcs/utils/ft_is.c \
				srcs/utils/ft_is_two.c \
				srcs/utils/x_to_str.c \
				srcs/utils/colors.c \
				srcs/utils/comm_printer.c \
				srcs/utils/ft_math.c \
				srcs/utils/ft_atoi.c \
	\
				srcs/reader/get_line.c \
	\
				srcs/parser/parser.c \
				srcs/parser/parser_utils.c \
				srcs/parser/parser_logic.c \
				srcs/parser/parse_command.c \
				srcs/parser/parse_expansion.c \
				srcs/parser/lexer.c \
				srcs/parser/lexer_utils.c \
				srcs/parser/ast.c \
	\
				srcs/cleaning/clean_shell.c \
				srcs/cleaning/clean_ast.c \

OBJS		:= $(SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%)

# Using wildcards: $(shell find $(HEADERS) -name *.h)
DEPS	=	includes/commands.h \
			includes/executing.h \
			includes/redirecting.h \
			includes/utils.h \
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
