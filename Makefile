# Project details
name = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g3  

# Directories
SRC_DIR = .
HEADER_DIR = header

# Source files
SRC =minishell.c \
    execution/cd.c \
	execution/free.c \
	execution/int_out_file.c \
	execution/run_builtin_in_pipe.c \
	execution/run_one_cmd.c \
	execution/echo.c \
	execution/envp.c \
	execution/get_path_cmd.c \
	execution/run_cmd_as_child.c \
	execution/env.c \
	execution/get_val.c \
	execution/print_export.c \
	execution/run_cmd.c \
	execution/exit.c \
	execution/heredoc.c \
	execution/pwd.c \
	execution/run_cmd_with_pipe.c \
	execution/unset.c \
	execution/export.c \
	execution/initialize_environment.c \
	execution/run_builtin.c \
	execution/run_one_builtin.c \
	execution/utils1.c \
	execution/utils2.c\
	execution/signal.c \
    parsing/ft_expending.c \
	parsing/ft_expand_her.c \
	parsing/lexer.c \
	parsing/parsing.c\
	parsing/apend_in_struct.c \
    tools/ft_error.c \
	tools/ft_is.c \
	tools/ft_catstr.c\
	tools/ft_strs.c \
	tools/ft_alloc.c \
	tools/ft_str.c \
	tools/ft_helper.c \
	tools/ft_signals.c \
	tools/ft_tools.c \
	tools/ft_free.c\
	parsing/apend_to_file.c\

# Object files
OBJ = $(SRC:%.c=%.o)

# Include headers
INC = -I $(HEADER_DIR)

# Targets
all: $(name)

$(name): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(name) -lreadline

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(name)

re: fclean all
