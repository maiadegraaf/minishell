NAME := libft.a
SRCFILES := \
	ft_atoi.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line/get_next_line_utils.c \
	get_next_line/get_next_line.c \
	ft_printf/ft_convert_hex.c \
	ft_printf/ft_determine_type.c \
	ft_printf/ft_if_char.c \
	ft_printf/ft_if_hex.c \
	ft_printf/ft_if_num.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_putstr_size.c \
	ft_printf/ft_putunsignedint_fd.c

OBJFILES = ${SRCFILES:%.c=%.o}

BONUS_SRCFILES := \
	ft_lstadd_front.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

BONUS_OBJFILES = ${BONUS_SRCFILES:%.c=%.o}

HEADERFILES := libft.h

CFLAGS	= -Wall -Wextra -Werror -g

ifdef WITH_BONUS
ALL_OBJS = $(OBJFILES) $(BONUS_OBJFILES)
else
ALL_OBJS = $(OBJFILES)
endif

all: libft.a

%.o: %.c $(HEADERFILES)
	@$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(ALL_OBJS)
	@ar -ru $(NAME) $^
	@echo "Libft succesfully created"

bonus: 
	@$(MAKE) WITH_BONUS=1

clean:
	@rm -f $(OBJFILES) $(BONUS_OBJFILES)

fclean: clean
	@rm -f $(NAME) $^

re: fclean all

.PHONY: clean fclean re bonus