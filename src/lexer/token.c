/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:27:03 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 17:37:08 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	if (!token)
		return ;
	free(token->value);
	free(token);
}

int	is_token_operator(t_token *token)
{
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT ||
			token->type == T_HEREDOC || token->type == T_APPEND);
}

static bool	is_valid(t_token *current, t_token *next)
{
	if ((i == 0 || i == (list_size - 1)) && current->type == T_PIPE)
	{
		print_syntax_error(current->value);
		return (false);
	}
	if (is_token_operator(current) && (!next || next->type != T_WORD))
	{
		print_syntax_error(next->value);
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
		if (!is_valid(current, next))
			return (0);
		token_list = token_list->next;
		i++;
	}
	return (1);
}
