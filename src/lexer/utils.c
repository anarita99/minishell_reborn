/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:54:04 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/09 14:59:58 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_word(char c)
{
	return (c != '\0' && !ft_iswhitespace(c) && !is_operator(c));
}

int	calc_consumed_chars(t_token_type token_type)
{
	if (token_type == T_WORD)
		return (0);
	if (token_type == T_REDIR_IN || token_type == T_REDIR_OUT)
		return (1);
	if (token_type == T_HEREDOC || token_type == T_APPEND)
		return (2);
	return (1);
}

void	print_syntax_error(const char *token_value)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token_value)
		write(2, token_value, ft_strlen(token_value));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}
