OS = $(shell uname)
CPU = $(shell uname -m)

# nom de l'executable
NAME = minishell

# Source and object diretories
SRCDIR = src
OBJDIR = obj

# Librairies
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

ifeq ($(OS), Darwin)
	ifeq ($(CPU), arm64)
		READLINE_LIB = -L /opt/homebrew/opt/readline/lib -lreadline
	else
		READLINE_LIB = -L /usr/local/opt/readline/lib -lreadline
	endif
else ifeq ($(OS), Linux)
	READLINE_LIB = -lreadline
endif
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g3 -fno-omit-frame-pointer -fstack-protector-all

ifeq ($(OS), Darwin)
	ifeq ($(CPU), arm64)
		INCLUDES = -I includes -I /opt/homebrew/opt/readline/include
	else
		INCLUDES = -I includes -I /usr/local/opt/readline/include
	endif
else ifeq ($(OS), Linux)
	INCLUDES = -I includes
endif

RM = rm -f

vpath %.c \
	$(SRCDIR) \
	$(SRCDIR)/builtin \
	$(SRCDIR)/executor \
	$(SRCDIR)/executor/exec \
	$(SRCDIR)/executor/heredoc \
	$(SRCDIR)/executor/pipe \
	$(SRCDIR)/executor/redir \
	$(SRCDIR)/expander \
	$(SRCDIR)/parser \
	$(SRCDIR)/lexer \
	$(SRCDIR)/signals \
	$(SRCDIR)/includes \
	$(SRCDIR)/utils \
	$(SRCDIR)/utils/byebye \
	$(SRCDIR)/utils/chain \
	$(SRCDIR)/utils/init \

# Sources and object files
# attention supprimer le testing.c
SRC = main.c \
builtin_utils.c cd.c echo.c env.c exit.c export.c pwd.c unset.c \
exec.c executor_utils.c \
heredoc.c \
pipe.c pipe_utils.c pipe_2.c \
redir.c redir_utils.c redir_setting.c \
expander.c expander_utils.c change_type.c env_utils.c init_env.c quotes.c var_handler.c\
lexer.c lexer_utils.c \
parser.c parser_utils.c \
signals.c \
error.c free.c \
init_chain.c \
struct.c \
testing.c \

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(LIBFT) $(NAME)

debug: CFLAGS = $(DEBUG_FLAGS)

debug: re

# Sanitize
sanitize: DEBUG_FLAGS += -fsanitize=address 
sanitize: debug 

# Rule to compile with Leaks check
leaks:
ifeq ($(OS), Darwin)
    MallocStackLogging=YES leaks --outputGraph=minishell.memgraph --fullContent --fullStackHistory --atExit -- ./$(NAME)
else ifeq ($(OS), Linux)
	valgrind --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --trace-children=yes --track-fds=all --default-suppressions=yes --suppressions=ignore_readline.supp ./$(NAME)
endif

$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)
	
# Compile each .c file to .o		
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME)

# Rule to clean up object files	
clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C $(LIBFTDIR)
		@rm -rf $(OBJDIR)

#Rule to clean  up object files and the library
fclean: clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(LIBFTDIR)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re debug sanitize