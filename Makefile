# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 15:37:54 by miduarte &        #+#    #+#              #
#    Updated: 2025/11/11 11:58:01 by adores & mi      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -Ilibft

#SRCS = \
	srcs/main.c \
	srcs/utils.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer.c \
	srcs/execute.c \
	srcs/execute_pipeline.c \
	srcs/launch.c \
	srcs/signals.c \
	srcs/parser/history.c \
	srcs/cmd_utils.c \
	srcs/parser/parser.c \
	srcs/heredoc.c \
	srcs/expansion.c \
	execution/builtin/builtin.c \
	execution/builtin/cd.c\
	execution/builtin/echo.c\
	execution/builtin/env.c\
	execution/builtin/exit.c\
	execution/builtin/pwd.c\
	execution/builtin/unset.c\#

SRCS = \
	minishell.c \
	execution/builtins/cd.c\
	execution/builtins/echo.c\
	execution/builtins/env_functions.c\
	execution/builtins/env.c\
	execution/builtins/exit.c\
	execution/builtins/pwd.c\
	execution/builtins/unset.c\
	execution/builtins/export.c\

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
