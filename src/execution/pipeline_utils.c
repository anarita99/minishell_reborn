/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:10:37 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 16:13:42 by adores           ###   ########.fr       */
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

void	clean_pipeline(int prev_read)
{
	int	i;
	int	w_status;

	i = 0;
	report_err(NULL, "pipe", true);
	while (sh_s()->pids[i] > 0)
	{
		waitpid(sh_s()->pids[i], &w_status, 0);
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	sh_s()->exit_status = 1;
	free(sh_s()->pids);
	sh_s()->pids = NULL;
}
