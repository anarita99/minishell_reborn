# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores <adores@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:15:31 by adores            #+#    #+#              #
#    Updated: 2026/02/19 16:04:46 by adores           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = minishell
SRCS_DIR = src
INCS_DIR = include

# Libft structure
LIBFT_DIR = libft
LIBFT_SRCS_DIR = $(LIBFT_DIR)
LIBFT_INCS_DIR = $(LIBFT_DIR)
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Files
MAIN 		= 	main print data
LEXER 		= 	lexer/lexer lexer/token lexer/types lexer/buffer lexer/states
PARSER 		= 	parser/parser parser/arguments parser/redirects parser/command
EXECUTE 	= 	execute/utils \
				execute/builtins/builtin \
				execute/builtins/cd\
				execute/builtins/echo\
				execute/builtins/env_functions\
				execute/builtins/env_functions2\
				execute/builtins/env\
				execute/builtins/exit\
				execute/builtins/pwd\
				execute/builtins/unset\
				execute/builtins/export\
				execute/ext_execute\
				execute/ext_utils \
				execute/executor \
				execute/redir \
				execute/heredoc \
				execute/pipeline

FILES 		= $(MAIN) $(LEXER) $(PARSER) $(EXECUTE)
SRCS 		= $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS 		= $(SRCS:.c=.o)

# Compiler and flags
CC = cc
INCLUDES = -I$(INCS_DIR) -I$(LIBFT_INCS_DIR)
CFLAGS = -g -Wall -Wextra -Werror $(INCLUDES)
RLFLAGS = -lreadline
RM = rm -f

# Rules
all: ${NAME}

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

${NAME}: ${OBJS} $(LIBFT_LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(RLFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
	
valgrind: ${NAME}
	valgrind --suppressions=rlbad.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes ./$(NAME)

# Phony targets
.PHONY: all clean fclean re valgrind