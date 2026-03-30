/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:02:29 by adores            #+#    #+#             */
/*   Updated: 2026/03/30 16:17:39 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_and_exit(char *scope, char *msg, int exit_code, bool err)
{
	report_err(scope, msg, err);
	exitclean(exit_code);
}

void	report_err(char *scope, char *msg, bool error)
{
	if (!scope && !msg && !error)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (scope)
	{
		ft_putstr_fd(scope, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg && error)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, 2);
	else if (error)
		ft_putendl_fd(strerror(errno), 2);
}

void	exitclean(unsigned char exit_code)
{
	free_env_list(sh_s()->env_list);
	overwrite_std(sh_s()->original_fds);
	ft_lstclear(&sh_s()->input_list, del_cmd);
	free(sh_s()->pids);
	exit(exit_code);
}
