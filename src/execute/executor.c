/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:35:06 by adores            #+#    #+#             */
/*   Updated: 2026/02/18 16:33:56 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(void)
{
	t_cmd	*tmp;
	// int	input_size;

	tmp = (t_cmd *)sh_s()->input_list->content;
	exe_heredocs(tmp);
	//heredoc
	if (is_builtin(tmp->argv))
		exe_builtin(tmp);
	else
		execute_ext(tmp);
}