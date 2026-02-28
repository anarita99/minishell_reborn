/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:15 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:02 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// echo                 = echo
// 'alas"da"mn$ec"'     = alas"da"mn$ec"
// "alas$wow"           = alaswow
// alas$ crazy          = alas crazy
// abc$a$ '$c"razy'		= abcabc $c"razy
void	expander(t_list **commands, t_env *env_list)
{
	t_list  *current_node;
	t_cmd   *current_cmd;
	int     i;
	int		size;
	
	current_node = *commands;
	while (current_node)
	{
		current_cmd = (t_cmd *)current_node->content;
		i = 0;
		while (current_cmd->argv[i])
		{
			size = counter(env_list, current_cmd->argv[i]);
			current_cmd->argv[i] = expand(env_list, current_cmd->argv[i], size);
			i++;
		}
		remove_empty_str(current_cmd->argv);
		current_node = current_node->next;
	}
}
