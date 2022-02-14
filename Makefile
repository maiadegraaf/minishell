NAME	=		pipex

SRCS	=		pipex.c parse_envp.c

FLAGS	=		-Wall -Werror -Wextra

LIBFT	=		libft/libft.a

HEADER	=		pipex.h

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS) $(HEADER)
	$(CC) $(LIBFT) $(SRCS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	make fclean -C libft

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all
