/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:54 by adores            #+#    #+#             */
/*   Updated: 2026/01/15 15:17:57 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env_list;
	prev = NULL;
	while(current)
	{
		if(ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				shell->env_list = current->next;
			else
				prev->next = current->next;
			free_node(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(char **args, t_shell *shell)
{
	int	i;

	shell->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (get_env_value(shell->env_list, args[i]))
			remove_env_var(shell, args[i]);
		i++;
	}
	return (0);
}
