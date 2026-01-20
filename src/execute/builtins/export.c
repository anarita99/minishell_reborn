/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:18:13 by adores            #+#    #+#             */
/*   Updated: 2026/01/15 15:18:15 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	bubble_sort_array(t_env **node_array)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (node_array[i])
	{
		j = 0;
		while(node_array[j + 1])
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

void	print_sorted_env(t_shell *shell)
{
	t_env	**node_array;
	int		i;

	node_array = list_to_array (shell->env_list);
	if (!node_array)
		return;
	bubble_sort_array(node_array);
	i = 0;
	while (node_array[i])
	{
		if (ft_strncmp(node_array[i]->key, "_", 2) != 0)
			printf("declare -x %s=\"%s\"\n", node_array[i]->key, node_array[i]->value);
		i++;
	}
	free(node_array);
}

bool	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if(!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (false);
	i++;
	while (str[i])
	{
		if ((str[i] == '=' || (str[i] == '+' && str[i + 1] == '=' )))
			break;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return(false);
		i++;
	}
	return (true);
}

static void	export_error(char *arg, int *exit_code)
{
	*exit_code = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	export_append(char *equal, char *plus, char *arg, t_shell *shell)
{
	t_env	*node;
	char	*value;

	*plus = '\0';
	node = get_env_node(shell->env_list, arg);
	if (node)
	{
		if (node->value)
		{
			value = ft_strjoin(node->value, equal + 1);
			if(!value)
				malloc_error(shell->env_list);
			free(node->value);
			node->value = value;
		}
		else
			set_env_var(&shell->env_list, node->key, equal + 1);
	}
	else
		set_env_var(&shell->env_list, arg, equal + 1);
	*plus = '+';
}

static void export_non_null_var(char *equal, char *plus, char *arg, t_shell *shell)
{
	
	if(equal && !plus)
	{
		*equal = '\0';
		set_env_var(&shell->env_list, arg, equal + 1);
		*equal = '=';
	}
	else if(plus)
		export_append(equal, plus, arg, shell);
}

int	export_builtin(char **args, t_shell *shell)
{
	int		exit_code;
	int		i;
	char	*equal;
	char	*plus;

	exit_code = 0;
	if (!args[1])
		return (print_sorted_env(shell), exit_code);
	i = 0;
	while(args[i])
	{
		equal = ft_strchr(args[i], '=');
		plus = ft_strchr(args[i], '+');
		if(is_valid_identifier(args[i]) == false)
			export_error(args[i], &exit_code);
		else if(equal)
			export_non_null_var(equal, plus, args[i], shell);
		else if(!get_env_node(shell->env_list, args[i]))
				set_env_var(&shell->env_list, args[i], NULL);
		i++;
	}
	return (exit_code);
}
