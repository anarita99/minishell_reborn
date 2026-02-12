# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: adores <adores@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:15:31 by adores            #+#    #+#              #
#    Updated: 2026/02/11 16:33:44 by adores           ###   ########.fr        #
=======
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2026/01/12 16:01:57 by leramos-         ###   ########.fr        #
>>>>>>> leo
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = minishell
SRCS_DIR = src
INCS_DIR = includes

<<<<<<< HEAD
SRCS = \
	minishell.c \
	src/execute/data.c \
	src/execute/utils.c \
	src/execute/execute.c \
	src/execute/builtins/cd.c\
	src/execute/builtins/echo.c\
	src/execute/builtins/env_functions.c\
	src/execute/builtins/env_functions2.c\
	src/execute/builtins/env.c\
	src/execute/builtins/exit.c\
	src/execute/builtins/pwd.c\
	src/execute/builtins/unset.c\
	src/execute/builtins/export.c\
	src/execute/ext_execute.c
=======
# Libft structure
LIBFT_DIR = libft
LIBFT_SRCS_DIR = $(LIBFT_DIR)/src
LIBFT_INCS_DIR = $(LIBFT_DIR)/includes
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Readline structure
READLINE_DIR = readline
>>>>>>> leo

# Files
FILES = main print lexer/lexer lexer/token lexer/types lexer/buffer lexer/states parser/command parser/parser
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
INCLUDES = -I$(INCS_DIR) -I$(LIBFT_INCS_DIR) -l$(READLINE_DIR)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
RM = rm -f

# Rules
all: ${NAME}

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

<<<<<<< HEAD
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus
=======
${NAME}: ${OBJS} $(LIBFT_LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME)
>>>>>>> leo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(NAME)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes ./$(NAME)

# Phony targets
.PHONY: all bonus clean fclean re valgrind