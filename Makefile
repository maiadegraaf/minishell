NAME	=	minishell

SRCS	=	./srcs/main.c \
			./srcs/parse_envp.c \
			# ./srcs/pipex/pipex.c \

OBJS	=	${SRCS:%.c=%.o}

FLAGS	=	-Wall -Werror -Wextra

LIBFT	=	./libraries/libft/libft.a

HEADER	=	./includes/minishell.h

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
