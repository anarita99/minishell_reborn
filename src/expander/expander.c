/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:15 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/09 02:19:22 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// echo                 = echo
// 'alas"da"mn$ec"'     = alas"da"mn$ec"
// "alas$wow"           = alaswow
// alas$ crazy          = alas crazy
// abc$a$ '$c"razy'		= abcabc $c"razy
// 'hello "w"orld'		= hello "w"orld
void	expander(t_list **commands, t_env *env_list, int exit_status)
{
	t_list  *current_node;
	t_cmd   *current_cmd;
	int     i;
	int		size;
	char	*old;
	char	*new;
	
	current_node = *commands;
	while (current_node)
	{
		current_cmd = (t_cmd *)current_node->content;
		i = 0;
		while (current_cmd->argv[i])
		{
			size = counter(env_list, exit_status, current_cmd->argv[i]);
			old = current_cmd->argv[i];
			new = expand(env_list, exit_status, current_cmd->argv[i], size);
			if (!new)
				return ;
			current_cmd->argv[i] = new;
			if (new[0] == '\0' && !has_quotes(old))
			{
				remove_from_array(current_cmd->argv, i);
				free(old);
				continue ;
			}
			free(old);
			i++;
		}
		i = 0;
		while (current_cmd->redirs && current_cmd->redirs[i].filename != NULL)
		{
			size = counter(env_list, exit_status, current_cmd->redirs[i].filename);
			old = current_cmd->redirs[i].filename;
			new = expand(env_list, exit_status, current_cmd->redirs[i].filename, size);
			if (!new)
				return ;
			current_cmd->redirs[i].filename = new;
			free(old);
			i++;
		}
		current_node = current_node->next;
	}
}
