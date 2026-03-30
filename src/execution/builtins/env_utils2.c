/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:01:50 by adores            #+#    #+#             */
/*   Updated: 2026/03/26 13:42:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envsize(t_env *env_list)
{
	int	count;

	if (!env_list)
		return (0);
	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list -> next;
	}
	return (count);
}

static char	*env_node_to_str(t_env *node)
{
	int		size;
	char	*str;

	size = ft_strlen(node->key) + 2;
	if (node->value)
		size += ft_strlen(node->value);
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, node->key, size);
	if (node->value != NULL)
	{
		ft_strlcat(str, "=", size);
		ft_strlcat(str, node->value, size);
	}
	return (str);
}

char	**envlist_to_char(t_env *env_list)
{
	char	**array;
	int		i;

	array = malloc((envsize(env_list) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		array[i] = env_node_to_str(env_list);
		if (!array[i])
			return (ft_freearray(array), NULL);
		env_list = env_list -> next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
