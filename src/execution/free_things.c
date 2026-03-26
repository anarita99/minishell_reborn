/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:08:04 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 16:08:26 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free_node(head);
		head = next;
	}
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
