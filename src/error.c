/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:54:04 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/19 14:56:43 by leramos--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_syntax_error(char *token_value)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token_value)
		write(2, token_value, ft_strlen(token_value));
	else
		write(2, "newline", 7); // For when a command ends with '>'
	write(2, "'\n", 2);
}
