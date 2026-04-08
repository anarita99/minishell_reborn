/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:52:37 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 19:52:51 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	is_valid(t_token *current, t_token *next, bool is_edge_token)
{
	if (is_edge_token && current->type == T_PIPE)
	{
		print_syntax_error(current->value);
		return (false);
	}
	if (is_token_operator(current) && (!next || next->type != T_WORD))
	{
		if (next)
			print_syntax_error(next->value);
		else
			print_syntax_error(NULL);
		return (false);
	}
	if (current->type == T_PIPE && next && next->type == T_PIPE)
	{
		print_syntax_error(current->value);
		return (false);
	}
	return (true);
}

int	validate_tokens(t_list *token_list)
{
	int		i;
	int		list_size;
	t_token	*current;
	t_token	*next;

	list_size = ft_lstsize(token_list);
	i = 0;
	while (i < list_size)
	{
		current = (t_token *)token_list->content;
		next = NULL;
		if (token_list->next)
			next = (t_token *)token_list->next->content;
		if (!is_valid(current, next, (i == 0 || i == (list_size - 1))))
			return (0);
		token_list = token_list->next;
		i++;
	}
	return (1);
}
