# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores <adores@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:15:31 by adores            #+#    #+#              #
#    Updated: 2026/02/11 16:33:44 by adores           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -Ilibft

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

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

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
