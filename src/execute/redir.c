/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:40 by adores            #+#    #+#             */
/*   Updated: 2026/02/18 17:37:54 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

void	open_file(t_redir redir, int *fd)
{
	t_token_type	type;

	type = redir.type;
	if (type == T_REDIR_IN || type == T_HEREDOC)
		fd[0] = open(redir.filename, O_RDONLY);
	if (type == T_REDIR_OUT)
		fd[1] = open(redir.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == T_APPEND)
		fd[1] = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

bool parse_redirects(t_cmd *cmd, int *fds)
{
	int		i;
	char	*name;
	t_token_type	n_type;

	i = -1;
	while(cmd->redirs[++i].filename != NULL)
	{
		name = cmd->redirs[i].filename;
		open_file(cmd->redirs[i], fds);
		if(fds[0] == -1 || fds[1] == -1)
			return (print_err(NULL, name, true), false);
		if (cmd->redirs[i + 1].filename != NULL)
		{
			n_type = cmd->redirs[i + 1].type;
			if (fds[0] > 0 && (n_type == T_REDIR_IN || n_type == T_HEREDOC))
				close(fds[0]);
			if (fds[1] > 0 && (n_type == T_REDIR_OUT || n_type == T_APPEND))
				close(fds[1]);
		}
	}
	return (true);
}

static void	save_og_fds(int *og_fd)
{
	og_fd[0] = dup(STDIN_FILENO);
	og_fd[1] = dup(STDOUT_FILENO);
}

int	setup_fds(t_cmd *input, int *og_fd, bool save)
{
	int	new_fd[2];

	new_fd[0] = 0;
	new_fd[1] = 0;
	if (save)
		save_og_fds(og_fd);
	if (input->redirs->filename == NULL)
		return(0);
	if (parse_redirects(input, new_fd) == false)
	{
		if(new_fd[0] > 0)
			close(new_fd[0]);
		if(new_fd[1] > 0)
			close(new_fd[1]);
		return (1);
	}
	overwrite_std(new_fd);
	return (0);
}

void	overwrite_std(int *fd)
{
	if (fd[0] > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] > 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}
