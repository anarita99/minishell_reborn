/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:27:03 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 20:09:29 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_token(t_token_type type, char *value)
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
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_HEREDOC || token->type == T_APPEND);
}

void	append_token_to_lst(t_list **lst, int token_type, t_sbuf *buf)
{
	char	*token_value;
	t_list	*current_node;
	t_token	*new_token;

	token_value = ft_strdup(buf->data);
	new_token = create_token(token_type, token_value);
	if (new_token)
	{
		current_node = ft_lstnew(new_token);
		ft_lstadd_back(lst, current_node);
	}
	sbuf_reset(buf);
}
