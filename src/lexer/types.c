/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:54:04 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/29 16:36:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int is_word(char c)
{
	return (c != '\0' && !ft_iswhitespace(c) && !is_operator(c));
}

t_token	*create_word(char *input, int start_idx, int end_idx)
{
	char	*value;
	int		value_size;
	int		i;

	value_size = end_idx - start_idx + 1;
	value = malloc(sizeof(char) * value_size + 1);
	i = 0;
	while (i < value_size)
	{
		value[i] = input[i + start_idx];
		i++;
	}
	value[i] = '\0';
	return (create_token(T_WORD, value));
}

t_token	*create_operator(t_token_type type, char *str)
{
	char	*value;
	int		len;

	len = ft_strlen(str);
	value = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(value, str, len + 1);
	return (create_token(type, value));
}
