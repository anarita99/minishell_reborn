/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:58 by adores            #+#    #+#             */
/*   Updated: 2026/02/11 16:34:11 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"

int	set_cd_path(char **args, char **path)
{
	if (!args[1])
	{
		*path = get_env_value(sh_s()->env_list, "HOME");
		if(*path == NULL)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*path = get_env_value(sh_s()->env_list, "OLDPWD");
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
	old_pwd = get_env_value(sh_s()->env_list, "PWD");
	if (set_cd_path(args, &path) == 1)
		return (1);
	if (chdir(path) == -1)
		return (print_err("cd", path, true), 1);
	new_pwd = getcwd(NULL, 0);
	if(!new_pwd)
	{
		new_pwd = ft_strjoin(old_pwd, "/..");
		if(!new_pwd)
			error_exit("malloc", "allocation error", 1, false);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	}
	set_env_var("OLDPWD", old_pwd);
	set_env_var("PWD", new_pwd);
	free(new_pwd);
	return (0);
}
