/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:45 by adores            #+#    #+#             */
/*   Updated: 2026/02/11 14:59:20 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		return (1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	return (0);
}

int	exe_builtin(char **args, t_shell *shell)
{
	if(!args || !args[0])
		return(1);
	if(ft_strcmp(args[0], "echo") == 0)
		return(echo_builtin(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return(cd_builtin(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return(pwd_builtin());
	if (ft_strcmp(args[0], "exit") == 0)
		return(exit_builtin(args));
	else if(ft_strcmp(args[0], "env") == 0)
		return(env_builtin(shell));
	else if(ft_strcmp(args[0], "unset") == 0)
		return(unset_builtin(args));
	else if(ft_strcmp(args[0], "export") == 0)
		return(export_builtin(args));
	return(1);
}
