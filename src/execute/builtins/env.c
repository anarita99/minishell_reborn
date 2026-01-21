/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:13:48 by adores            #+#    #+#             */
/*   Updated: 2026/01/21 15:58:06 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"


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
			malloc_error();
		return ;
	}
	set_env_var("SHLVL", "1");
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
	char		buf[PATH_MAX];

	i = 0;
	
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		if (add_env_var(&call_sh_struct()->env_list, environ[i]) == 1)
			malloc_error();
		i++;
	}
	set_env_var("PWD", getcwd(buf, PATH_MAX));
	set_shell_level(&call_sh_struct()->env_list);
	return (call_sh_struct()->env_list);
}

int	env_builtin()
{
	t_env	*current;

	current = call_sh_struct()->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	call_sh_struct()->last_exit_status = 0;
	return (0);
}
