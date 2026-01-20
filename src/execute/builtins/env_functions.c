/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:33 by adores            #+#    #+#             */
/*   Updated: 2026/01/15 15:17:34 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
		free(str[--i]);
	free(str);
}

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

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void free_env_list(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free_node(head);
		head = next;
	}
}

void	set_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*current_node;

	current_node = get_env_node(*env_list, key);
	if (current_node)
	{
		free(current_node->value);
		current_node->value = ft_strdup(value);
		if(!current_node->value)
			malloc_error(*env_list);     //malloc exit
		return ;
	}
	current_node = env_new_node(NULL, NULL);
	if(!current_node)
		malloc_error(*env_list);      //malloc exit
	current_node->key = ft_strdup(key);
	current_node->value = ft_strdup(value);
	if (!current_node->key || !current_node->value)
		return (free_node(current_node));
	env_add_back(env_list, current_node);
}

