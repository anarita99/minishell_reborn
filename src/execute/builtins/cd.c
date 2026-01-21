/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:58 by adores            #+#    #+#             */
/*   Updated: 2026/01/21 15:08:42 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	write(2, ": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int	set_cd_path(char **args, char **path)
{
	if (!args[1])
	{
		*path = get_env_value(call_sh_struct()->env_list, "HOME");
		if(*path == NULL)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*path = get_env_value(call_sh_struct()->env_list, "OLDPWD");
		if(*path == NULL)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		printf("%s\n", *path);
	}
	else
		*path = args[1];
	return (0);
}

int cd_builtin (char **args)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	old_pwd = get_env_value(call_sh_struct()->env_list, "PWD");
	if (set_cd_path(args, &path) == 1)
		return (1);
	if (chdir(path) == -1)
		return (cd_error(args[1]), 1);
	new_pwd = getcwd(NULL, 0);
	if(!new_pwd)
	{
		free_str_array(args);
		malloc_error();
	}
	set_env_var("OLDPWD", old_pwd);
	set_env_var("PWD", new_pwd);
	free(new_pwd);
	return (0);
}

//verificar erros