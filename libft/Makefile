# Library name
NAME = libft.a

# Source and object diretories
SRCDIR = .
OBJDIR = $(SRCDIR)

# Sources and object files
SOURCE = ft_strlen.c \
         ft_memmove.c \
         ft_memcpy.c \
         ft_strlcpy.c \
         ft_strlcat.c \
         ft_isalpha.c \
         ft_isdigit.c \
         ft_isalnum.c \
         ft_isascii.c \
         ft_isprint.c \
		 ft_isspace.c \
         ft_memset.c \
         ft_bzero.c \
         ft_toupper.c \
         ft_tolower.c \
         ft_strchr.c \
		 ft_strcmp.c \
         ft_strrchr.c \
         ft_strncmp.c \
         ft_memchr.c \
         ft_memcmp.c \
         ft_strnstr.c \
         ft_atoi.c \
         ft_calloc.c \
         ft_strdup.c \
		 ft_strndup.c \
         ft_substr.c \
         ft_strjoin.c \
		 ft_strjoin_free.c \
         ft_strtrim.c \
		 ft_itoa.c \
         ft_putchar_fd.c \
         ft_putstr_fd.c \
         ft_putendl_fd.c \
         ft_putnbr_fd.c \
		 ft_striteri.c \
		 ft_strmapi.c \
		 ft_split.c \
		 ft_atol.c \
		 get_next_line.c \
		 ft_strcmp.c \

SRCBONUS = 	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \

OBJS = $(addprefix $(OBJDIR)/, $(SOURCE:.c=.o))
OBJSBONUS = $(addprefix $(OBJDIR)/, $(SRCBONUS:.c=.o))

# Header file directory
INCLUDES = -I ../includes

# Compiler and flags
COMPILE = gcc
CFLAGS = -Wall -Wextra -Werror

# Default rule: make all is equivalent to make libft.a
all: $(NAME)

# Rule to create the static library libft.a
$(NAME): $(OBJS)
	@echo "Creating library $(NAME)..."
	ar -rcs $(NAME) $(OBJS)
	@echo "$(NAME) created successfully."

# Rule to add bonus functions to libft.a
bonus: $(OBJSBONUS)
	@echo "Adding bonus functions to $(NAME)..."
	ar -rcs $(NAME) $(OBJSBONUS)
	@echo "Bonus functions added to $(NAME) successfully."

# Compile each .c file to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	$(COMPILE) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to clean up object files
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS) 

#Rule to clean  up object files and the library
fclean: clean
	@echo "Cleaning library $(NAME)..."
	rm -f $(NAME)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re