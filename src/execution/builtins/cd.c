/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:58 by adores            #+#    #+#             */
/*   Updated: 2026/03/27 16:40:06 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_target(char **args)
{
	char	*target;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = get_env_value(sh_s()->env_list, "HOME");
		if (!target)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (target);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value(sh_s()->env_list, "OLDPWD");
		if (!target)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
			printf("%s\n", target);
		return (target);
	}
	return (args[1]);
}

int	cd_builtin(char **args)
{
	char	*target;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	old_pwd = get_env_value(sh_s()->env_list, "PWD");
	target = get_cd_target(args);
	if (!target)
		return (1);
	if (chdir(target) == -1)
		return (report_err("cd", target, true), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 2);
		new_pwd = ft_strjoin(old_pwd, "/..");
		if (!new_pwd)
			err_and_exit("malloc", "allocation error", 1, false);
	}
	set_env_var("OLDPWD", old_pwd);
	set_env_var("PWD", new_pwd);
	free(new_pwd);
	return (0);
}
