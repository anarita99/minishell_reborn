/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:54 by adores            #+#    #+#             */
/*   Updated: 2026/01/21 15:01:35 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	remove_env_var(char *key)
{
	t_env	*current;
	t_env	*prev;

	current = call_sh_struct()->env_list;
	prev = NULL;
	while(current)
	{
		if(ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				call_sh_struct()->env_list = current->next;
			else
				prev->next = current->next;
			free_node(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(char **args)
{
	int	i;

	call_sh_struct()->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (get_env_value(call_sh_struct()->env_list, args[i]))
			remove_env_var(args[i]);
		i++;
	}
	return (0);
}
