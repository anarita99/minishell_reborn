/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:35:06 by adores            #+#    #+#             */
/*   Updated: 2026/02/19 16:16:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(void)
{
	t_cmd	*tmp;
	int	input_size;

	tmp = (t_cmd *)sh_s()->input_list->content;
	input_size = ft_lstsize(sh_s()->input_list);
	if (input_size == 1)
	{
		exe_heredocs(tmp);
		if (is_builtin(tmp->argv))
			exe_builtin(tmp);
		else
			execute_ext(tmp);
	}
	//else
		//execute_pipeline
		//wait_children
}
