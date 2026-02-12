/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 15:55:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Input: ls -la | echo hello >> output.txt
// Tokens: [WORD: "ls"], [WORD: "-la"], [PIPE: "|"], [WORD: "echo"], [WORD: "hello"], [APPEND: ">>"], [WORD: "output.txt"]

// Output: t_list of t_cmd:
//
//	argv: ["ls", "-la", NULL]
//	redirs: NULL
//
//	argv: ["echo", "hello", NULL]
//	redirs: [APPEND : "output.txt" : FALSE]

t_list	*parser(t_token *head)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*cmd_node;
	t_token *current_token;

	cmd_list = NULL;
	current_token = head;
	
	while (current_token)
	{
		cmd = get_next_cmd(current_token);
		if (!cmd)
			break;
		cmd_node = ft_lstnew(cmd);
		if (!cmd_node)
		{
			del_cmd(cmd);
			break;
		}
		ft_lstadd_back(&cmd_list, cmd_node);
		while (current_token && current_token->type != T_PIPE)
			current_token = current_token->next;
		if (current_token && current_token->type == T_PIPE)
			current_token = current_token->next;
	}
	return (cmd_list);
}
