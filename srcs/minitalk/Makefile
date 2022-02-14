# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fpolycar <fpolycar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/15 10:49:26 by fpolycar      #+#    #+#                  #
#    Updated: 2022/02/04 14:06:57 by fpolycar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar ru
RM = rm -f
LIBFT = ./libft/libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@make bonus -C libft

$(SERVER): server.o minitalk.h
	$(CC) server.o $(LIBFT) -o $@
	@printf "\e[38;5;226m./$@ successfully build\e[0m\n"

$(CLIENT): client.o minitalk.h
	$(CC) client.o $(LIBFT) -o $@
	@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@make clean -C libft
	$(RM) *.o

fclean: clean
	@make fclean -C libft
	rm -f $(CLIENT) $(SERVER)

re: fclean all
