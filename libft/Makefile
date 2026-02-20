# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2025/10/15 14:21:48 by leramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = libft.a
SRCS_DIR = src
INCS_DIR = include

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR)
AR = ar rcs
RM = rm -f

# Files
FILES = ft_atoi ft_bzero ft_calloc ft_isalnum \
		ft_isalpha ft_isascii ft_isdigit ft_isprint \
		ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memset \
		ft_putchar_fd ft_putendl_fd ft_putnbr_fd \
		ft_putstr_fd ft_split ft_strchr ft_strdup \
		ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
		ft_strlen ft_strmapi ft_strncmp ft_strnstr \
		ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper \
		ft_lstadd_back ft_lstadd_front ft_lstclear \
		ft_lstdelone ft_lstiter ft_lstlast \
		ft_lstmap ft_lstnew ft_lstsize

FILES += get_next_line get_next_line_utils
FILES += ft_printf ft_printf_utils ft_printf_specifiers ft_printf_output

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS = $(SRCS:.c=.o)

# Rules
all: ${NAME}

${NAME}: ${OBJS}
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re