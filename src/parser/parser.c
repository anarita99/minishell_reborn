/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/04 15:43:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parser(t_token *head)
{
	t_list	*cmd_list;
	t_list	*current_node;
	t_cmd	*current_cmd;
	t_token	*current_token;

	cmd_list = NULL;
	current_token = head;
	while (current_token)
	{
		current_cmd = get_next_cmd(current_token);
		if (!current_cmd)
			break ;
		current_node = ft_lstnew(current_cmd);
		if (!current_node)
		{
			del_cmd(current_cmd);
			break ;
		}
		ft_lstadd_back(&cmd_list, current_node);
		while (current_token && current_token->type != T_PIPE)
			current_token = current_token->next;
		if (current_token)
			current_token = current_token->next;
	}
	return (cmd_list);
}
