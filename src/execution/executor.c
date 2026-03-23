/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:35:06 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 15:57:11 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_children(int pid_size)
{
	int	i;
	int	w_status;

	w_status = 0;
	i = -1;
	if (!sh_s()->pids)
		return ;
	while (++i < pid_size)
	{
		if (sh_s()->pids[i] > 0)
			waitpid(sh_s()->pids[i], &w_status, 0);
	}
	if (sh_s()->exit_status != 700)
		handle_wait_status(w_status);
	else
		sh_s()->exit_status = 130;
	free(sh_s()->pids);
	sh_s()->pids = NULL;
}

void	executor(void)
{
	t_cmd	*tmp;
	int		input_size;

	tmp = (t_cmd *)sh_s()->input_list->content;
	input_size = ft_lstsize(sh_s()->input_list);
	executor_signals();
	if (input_size == 1)
	{
		exe_heredocs(tmp);
		if (sh_s()->exit_status == 700)
		{
			sh_s()->exit_status = 130;
			return ;
		}
		if (is_builtin(tmp->argv))
			exe_builtin(tmp);
		else
			execute_ext(tmp);
	}
	else
	{
		exe_pipeline(input_size);
		wait_children(input_size);
	}
}
