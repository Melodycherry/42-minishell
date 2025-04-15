NAME = ft_printf.a

SRCDIR = .
OBJDIR = $(SRCDIR)

SRC =	ft_printf.c \
		ft_number.c \
		ft_pointer.c \
		ft_hexa.c \
		ft_unsigned_int.c \
		ft_putchar_len.c \
		ft_string.c \

OBJS = $(SRC:%.c=%.o)

INCLUDES = -I ../includes

CC = gcc

RM = rm -f 

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re