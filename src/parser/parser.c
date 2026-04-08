/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/07 18:34:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	advance_past_pipe(t_list **token_list)
{
	t_token	*current_token;
	bool	continue_loop;

	continue_loop = true;
	while (*token_list && continue_loop)
	{
		current_token = (t_token *)(*token_list)->content;
		if (current_token->type == T_PIPE)
			continue_loop = false;
		*token_list = (*token_list)->next;
	}
}

t_list	*parser(t_list *token_list)
{
	t_list	*cmd_list;
	t_list	*current_cmd_node;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	while (token_list)
	{
		new_cmd = get_next_cmd(token_list);
		if (!new_cmd)
		{
			ft_lstclear(&cmd_list, del_cmd);
			return (NULL);
		}
		current_cmd_node = ft_lstnew(new_cmd);
		if (!current_cmd_node)
		{
			del_cmd(new_cmd);
			ft_lstclear(&cmd_list, del_cmd);
			return (NULL);
		}
		ft_lstadd_back(&cmd_list, current_cmd_node);
		advance_past_pipe(&token_list);
	}
	return (cmd_list);
}
