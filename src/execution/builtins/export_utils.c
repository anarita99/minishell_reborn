/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:48:15 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 15:52:53 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bubble_sort_array(t_env **node_array)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (node_array[i])
	{
		j = 0;
		while (node_array[j + 1])
		{
			if (ft_strcmp(node_array[j]->key, node_array[j + 1]->key) > 0)
			{
				temp = node_array[j];
				node_array[j] = node_array[j + 1];
				node_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static t_env	**list_to_array(t_env	*env_list)
{
	int		i;
	t_env	**node_array;

	i = 0;
	node_array = malloc((1 + env_lstsize(env_list)) * sizeof(t_env *));
	if (!node_array)
		return (NULL);
	while (env_list)
	{
		node_array[i] = env_list;
		i++;
		env_list = env_list->next;
	}
	node_array[i] = NULL;
	return (node_array);
}

void	print_sorted_env(void)
{
	t_env	**node_array;
	int		i;

	node_array = list_to_array (sh_s()->env_list);
	if (!node_array)
		return ;
	bubble_sort_array(node_array);
	i = 0;
	while (node_array[i])
	{
		if (ft_strncmp(node_array[i]->key, "_", 2) != 0)
		{
			printf("declare -x %s", node_array[i]->key);
			if (node_array[i]->value != NULL)
				printf("=\"%s\"", node_array[i]->value);
			printf("\n");
		}
		i++;
	}
	free(node_array);
}
