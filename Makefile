# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2026/01/09 14:54:51 by leramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = minishell
SRCS_DIR = src
INCS_DIR = includes

# Libft structure
LIBFT_DIR = libft
LIBFT_SRCS_DIR = $(LIBFT_DIR)/src
LIBFT_INCS_DIR = $(LIBFT_DIR)/includes

# Readline structure
READLINE_DIR = readline

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -I$(LIBFT_INCS_DIR) -l$(READLINE_DIR)
AR = ar rcs
RM = rm -f

# Files
FILES = main lexer/lexer lexer/token lexer/types
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

# Rules
all: ${NAME}

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

${NAME}: ${OBJS} $(LIBFT_LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME)

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

# Phony targets
.PHONY: all bonus clean fclean re