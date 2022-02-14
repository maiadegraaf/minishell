NAME	=		pipex

SRCS	=		srcs/pipex.c
				srcs/parse_envp.c
				srcs/main.c

FLAGS	=		-Wall -Werror -Wextra

LIBFT	=		libft/libft.a

HEADER	=		includes/minishell.h

all: $(NAME)

%.o: %.c $(HEADER)
	@echo "Compiling ${notdir $<}"
	@$(CC) -c $(CFLAGS) -I includes -o $@ $<

$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	@$(CC) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "Success"

$(LIBFT):
	$(MAKE) -C libft

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all
