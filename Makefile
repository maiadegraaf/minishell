NAME	=	minishell

SRCS	=	./srcs/main.c \
			./srcs/parse_envp.c \
			./srcs/utils/t_simple_cmds_utils.c \
			./srcs/utils/t_lexor_utils.c \
			./srcs/utils/utils.c \
			./srcs/lexor/token_reader.c \
			./srcs/lexor/handle_token.c \
			./srcs/parser/parser.c \
			./srcs/builtins/builtins.c \
			./srcs/builtins/mini_cd.c \
			./srcs/builtins/mini_echo.c \
			./srcs/builtins/mini_exit.c \
			./srcs/builtins/mini_export.c \
			./srcs/builtins/mini_pwd.c \
			./srcs/builtins/mini_unset.c \
			./srcs/builtins/mini_env.c \
			./srcs/executor/executor.c \
			# ./srcs/parser/parse_args.c \
			# ./srcs/pipex/pipex.c
			

OBJS	=	${SRCS:%.c=%.o}

FLAGS	=	-Wall -Werror -Wextra -g

LIBFT	=	./libraries/libft/libft.a

HEADER	=	./includes/minishell.h \
			./includes/lexor.h \
			./includes/builtins.h \
			./includes/utils.h \
			./includes/parser.h \
			./includes/executor.h

all: $(NAME)

%.o: %.c $(HEADER)
	@echo "Compiling ${notdir $<}"
	@$(CC) -c $(FLAGS) -I includes -o $@ $<

$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) -lreadline -o $(NAME)
	@echo "Success"

$(LIBFT):
	$(MAKE) -C ./libraries/libft

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@make fclean -C libraries/libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all
