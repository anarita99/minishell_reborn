/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/04 00:00:00 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}

	if (cmd->redirs)
	{
		i = 0;
		while (cmd->redirs[i].type != T_NONE)
		{
			if (cmd->redirs[i].filename)
				free(cmd->redirs[i].filename);
			i++;
		}
		free(cmd->redirs);
	}

	free(cmd);
}
