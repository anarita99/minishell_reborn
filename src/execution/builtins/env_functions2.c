/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:01:50 by adores            #+#    #+#             */
/*   Updated: 2026/03/26 13:42:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

char	**envlist_to_char(t_env *env_list)
{
	char	**array;
	int		size;
	int		i;

	array = malloc((envsize(env_list) + 1) * sizeof(char *));
	if(!array)
		return (NULL);
	i = 0;
	while(env_list)
	{
		size = ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2; //por causa do igual
		array[i] = 	malloc(sizeof(char) * size);
		if (!array[i])
			return (ft_freearray(array), NULL);
		ft_strlcpy(array[i], env_list->key, size);
		if (env_list->value != NULL)
		{
			ft_strlcat(array[i], "=", size);
			ft_strlcat(array[i], env_list->value, size);
		}
		env_list = env_list -> next;
		i++;
	}
	array[i] = NULL;
	return(array);
}
