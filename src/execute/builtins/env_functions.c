/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:33 by adores            #+#    #+#             */
/*   Updated: 2026/01/26 12:17:25 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

int	env_lstsize(t_env *lst)
{
	t_env	*temp;
	int		i;

	if (!lst)
		return (0);
	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	env_add_back(t_env **lst, t_env *node)
{
	t_env	*temp;

	if (!node || !lst)
		return ;
	temp = *lst;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

t_env	*env_new_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*get_env_value(t_env *env_list, char *key)
{
	char *value;

	while(env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			value = env_list->value;
			return (value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

t_env	*get_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
