/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:56:31 by adores & mi       #+#    #+#             */
/*   Updated: 2025/11/24 12:37:49 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//fazer funçao do shell level
//pwd, shell level quando env -i

static void	set_shell_level(t_env **env_list)
{
	t_env	*node;
	int		num;

	node = get_env_node(*env_list, "SHLVL");
	if(node)
	{
		num = ft_atoi(node->value);
		free(node->value);
		num += 1;
		node->value = ft_itoa(num);
		if (!node->value)
			malloc_error(*env_list);
		return ;
	}
	set_env_var(env_list, "SHLVL", "1");
}

int 	add_env_var(t_env **head, char *env)
{
	char 	*equal_sign;
	char	*key;
	char	*value;
	t_env	*new_node;

	equal_sign = ft_strchr(env, '=');
	key = ft_substr(env, 0, equal_sign - env);
	value = ft_strdup(equal_sign + 1);
	if(!key || !value)
		return (free(key), free(value), 1);
	new_node = env_new_node(key, value);
	if(!new_node)
		return (free(key), free(value), 1);
	env_add_back(head, new_node);
	return(0);
}

t_env	*init_env(void)
{
	extern char **environ;
	int			i;
	t_env		*env_list;
	char		buf[PATH_MAX];

	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		if (add_env_var(&env_list, environ[i]) == 1)
			malloc_error(env_list);
		i++;
	}
	set_env_var(&env_list, "PWD", getcwd(buf, PATH_MAX));
	set_shell_level(&env_list);
	return (env_list);
}

int	env_builtin(t_shell *shell)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	shell->last_exit_status = 0;
	return (0);
}
