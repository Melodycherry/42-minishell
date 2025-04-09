
# nom de l'executable
NAME = minishell

# Source and object diretories
SRCDIR = src
OBJDIR = obj

# Librairies
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
PRINTFDIR = ./ft_printf
PRINTF = $(PRINTFDIR)/libftprintf.a

# Compiler and flags
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
INCLUDE = -I include

RM = rm -f 

vpath %.c \
	$(SRCDIR) \
	$(SRCDIR)/builtin \
	$(SRCDIR)/executor \
	$(SRCDIR)/expander \
	$(SRCDIR)/parser \
	$(SRCDIR)/includes \
	$(SRCDIR)/utils \
	$(SRCDIR)/lexer \

# Sources and object files
SRC = main.c
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)

$(PRINTF):
	$(MAKE) all -C $(PRINTFDIR)
	
# Compile each .c file to .o		
$(OBJDIR)/%.o: %.c
		@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

# Rule to clean up object files	
clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C $(LIBFTDIR)
		$(MAKE) clean -C $(PRINTFDIR)
		@rm -rf $(OBJDIR)

#Rule to clean  up object files and the library
fclean: clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(LIBFTDIR)
		$(MAKE) fclean -C $(PRINTFDIR)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re