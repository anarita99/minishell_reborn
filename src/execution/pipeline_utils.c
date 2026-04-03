/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:10:37 by adores            #+#    #+#             */
/*   Updated: 2026/03/31 10:45:53 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_all_heredocs(t_list *input)
{
	t_list	*current;

	current = input;
	while (current)
	{
		exe_heredocs((t_cmd *)current->content);
		if (sh_s()->exit_status == 700)
		{
			return (0);
		}
		current = current->next;
	}
	return (1);
}

static void	wait_all_pipes(void)
{
	int	i;
	int	w_status;

	i = 0;
	while (sh_s()->pids[i] > 0)
	{
		waitpid(sh_s()->pids[i], &w_status, 0);
		i++;
	}
}

void	clean_pipeline(int prev_read)
{
	report_err(NULL, "pipe", true);
	wait_all_pipes();
	if (prev_read != -1)
		close(prev_read);
	sh_s()->exit_status = 1;
	free(sh_s()->pids);
	sh_s()->pids = NULL;
}

void	child_pipes(int i, int input_size)
{
	child_signals();
	sh_s()->is_child = true;
	if (i < input_size - 1)
	{
		close(sh_s()->pipe_fds[0]);
		dup2(sh_s()->pipe_fds[1], STDOUT_FILENO);
		close(sh_s()->pipe_fds[1]);
	}
	if (sh_s()->prev_read != -1)
	{
		dup2(sh_s()->prev_read, STDIN_FILENO);
		close(sh_s()->prev_read);
	}
}
