/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/07 18:14:12 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*get_next_cmd(t_list *current_node)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = get_argv(current_node);
	cmd->redirs = get_redirs(current_node);
	return (cmd);
}

static bool	is_file_heredoc(char *filename)
{
	return (ft_strncmp(filename, "/tmp/heredoc_minishell_", 23) == 0);
}

static void	free_redirs(t_redir *redirs)
{
	int				i;
	char			*filename;

	if (!redirs)
		return ;
	i = 0;
	while (redirs[i].type != T_NONE)
	{
		filename = redirs[i].filename;
		if (redirs[i].type == T_HEREDOC && is_file_heredoc(filename))
			unlink(filename);
		if (filename)
			free(filename);
		i++;
	}
	free(redirs);
}

void	del_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (!cmd)
		return ;
	ft_freearray(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}
