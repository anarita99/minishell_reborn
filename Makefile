# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores <adores@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:15:31 by adores            #+#    #+#              #
#    Updated: 2026/04/03 14:09:12 by adores           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME 			= 	minishell
SRCS_DIR 		= 	src
INCS_DIR 		= 	include

# Libft structure
LIBFT_DIR 		= 	libft
LIBFT_SRCS_DIR 	= 	$(LIBFT_DIR)/src
LIBFT_INCS_DIR 	= 	$(LIBFT_DIR)/include
LIBFT_LIB 		= 	$(LIBFT_DIR)/libft.a

# Files
MAIN 			= 	main print error sig
LEXER 			= 	lexer token types states
PARSER 			= 	parser arguments redirects command
EXPANDER		=	expander utils scan_word
EXECUTOR 		= 	utils \
					free_things \
					builtins/builtin \
					builtins/cd \
					builtins/echo \
					builtins/env_utils \
					builtins/env_utils2 \
					builtins/env \
					builtins/exit \
					builtins/pwd \
					builtins/unset \
					builtins/export \
					builtins/export_utils \
					ext_execute \
					ext_utils \
					executor \
					redir \
					heredoc \
					heredoc_utils \
					pipeline \
					pipeline_utils

FILES 			= 	$(MAIN) \
					$(addprefix lexer/, $(LEXER)) \
					$(addprefix parser/, $(PARSER)) \
					$(addprefix expander/, $(EXPANDER)) \
					$(addprefix execution/, $(EXECUTOR))
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS 			= 	$(SRCS:.c=.o)

# Compiler and flags
CC 				= 	cc
INCLUDES 		= 	-I$(INCS_DIR) -I$(LIBFT_INCS_DIR)
CFLAGS 			= 	-g -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS 		= 	-lreadline
RM 				= 	rm -f

# Rules
all: ${NAME}

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

${NAME}: ${OBJS} $(LIBFT_LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)

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
