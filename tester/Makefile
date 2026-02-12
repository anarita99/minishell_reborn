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
LIBFT_INCS_DIR		= $(LIBFT_DIR)/include
LIBFT_LIB			= $(LIBFT_DIR)/libft.a

# Minishell structure
MINISHELL_DIR		= ../
MINISHELL_SRCS_DIR	= $(MINISHELL_DIR)/src
MINISHELL_INCS_DIR	= $(MINISHELL_DIR)/include

# Files
MINISHELL_SRCS		= $(wildcard $(MINISHELL_SRCS_DIR)/lexer/*.c) \
                      $(wildcard $(MINISHELL_SRCS_DIR)/parser/*.c)

SRCS				= tester.c \
					  utils.c \
					  lexer/lexer_tests.c lexer/lexer_build.c lexer/lexer_compare.c \
					  parser/parser_tests.c parser/parser_build.c parser/parser_compare.c

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

valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes ./$(NAME)

.PHONY: all clean fclean re test lexer parser valgrind
