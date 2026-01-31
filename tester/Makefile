# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#              #
#    Updated: 2026/01/12 16:01:20 by leramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME				= minishell_tester
INCS_DIR			= .

# Libft structure
LIBFT_DIR			= ../libft
LIBFT_INCS_DIR		= $(LIBFT_DIR)/includes
LIBFT_LIB			= $(LIBFT_DIR)/libft.a

# Minishell structure
MINISHELL_DIR		= ../
MINISHELL_SRCS_DIR	= $(MINISHELL_DIR)/src
MINISHELL_INCS_DIR	= $(MINISHELL_DIR)/includes

# Files
MINISHELL_SRCS		= $(MINISHELL_SRCS_DIR)/lexer/lexer.c \
					  $(MINISHELL_SRCS_DIR)/lexer/token.c \
					  $(MINISHELL_SRCS_DIR)/lexer/types.c \
					  $(MINISHELL_SRCS_DIR)/lexer/buffer.c \
					  $(MINISHELL_SRCS_DIR)/lexer/states.c \
					  $(MINISHELL_SRCS_DIR)/parser/parser.c

SRCS				= tester.c \
					  utils.c \
					  tests/test_lexer.c \
					  tests/test_parser.c

MINISHELL_OBJS		= $(MINISHELL_SRCS:.c=.o)
OBJS				= $(SRCS:.c=.o)

# Compiler and flags
CC					= cc
INCLUDES			= -I$(MINISHELL_INCS_DIR) -I$(LIBFT_INCS_DIR) -I$(INCS_DIR)
CFLAGS				= -Wall -Wextra -Werror -g $(INCLUDES)
RM					= rm -f

# Rules
all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C ../libft

$(NAME): $(OBJS) $(MINISHELL_OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MINISHELL_OBJS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MINISHELL_OBJS)
	@make -C ../libft clean

fclean: clean
	$(RM) $(NAME)
	@make -C ../libft fclean

re: fclean all

test: all
	@./$(NAME)

lexer: all
	@./$(NAME) lexer

parser: all
	@./$(NAME) parser

.PHONY: all clean fclean re test test_lexer test_parser
