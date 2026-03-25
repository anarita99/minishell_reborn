/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/25 14:01:07 by adores           ###   ########.fr       */
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

static void	free_arr(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
			if (cmd->redirs[i].type == T_HEREDOC && \
ft_strncmp(cmd->redirs[i].filename, "/tmp/heredoc_minishell_", 23) == 0)
				unlink(cmd->redirs[i].filename);
			if (cmd->redirs[i].filename)
				free(cmd->redirs[i].filename);
			i++;
		}
		free(cmd->redirs);
	}
	free(cmd);
}
