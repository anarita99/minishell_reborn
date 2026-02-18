/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/18 18:11:41 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_next_cmd(t_token *current_token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = get_argv(current_token);
	cmd->redirs = get_redirs(current_token);
	return (cmd);
}

void	del_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)cmd_ptr;
	if (!cmd)
		return ;
	free_arr(cmd->argv);
	if (cmd->redirs)
	{
		i = 0;
		while (cmd->redirs[i].type != T_NONE)
		{
			if (cmd->redirs[i].type == T_HEREDOC && ft_strncmp(cmd->redirs[i].filename, "minishell-heredoc-", 18) == 0)
				unlink(cmd->redirs[i].filename);
			if (cmd->redirs[i].filename)
				free(cmd->redirs[i].filename);
			i++;
		}
		free(cmd->redirs);
	}
	free(cmd);
}
