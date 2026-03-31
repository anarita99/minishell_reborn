/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:48 by adores            #+#    #+#             */
/*   Updated: 2026/03/31 15:40:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_file(char **name, int *num)
{
	char	*fileno;
	int		counter;
	int		fd;

	counter = 0;
	while (true)
	{
		fileno = ft_itoa(counter++);
		*name = ft_strjoin("/tmp/heredoc_minishell_-", fileno);
		free(fileno);
		if (!*name)
			err_and_exit("malloc", "Allocation Error", 1, false);
		fd = open(*name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0644);
		if (fd != -1)
		{
			*num = fd;
			break ;
		}
		if (errno != EEXIST)
		{
			free(*name);
			err_and_exit("heredoc", "open", 1, true);
		}
		free(*name);
	}
}

static void	write_heredoc(t_redir *heredoc, int filefd)
{
	char	*input;
	char	*processed_input;

	while (true)
	{
		input = readline(">");
		if (!input && sh_s()->exit_status == 700)
			return ;
		else if (!input)
			return (heredoc_eof_warning(heredoc->filename));
		if (ft_strcmp(input, heredoc->filename) == 0)
			return (free(input));
		if (!heredoc->quoted)
			processed_input = expand_filename(input, sh_s()->env_list, \
sh_s()->exit_status, NULL);
		else
			processed_input = input;
		ft_putendl_fd(processed_input, filefd);
		free(processed_input);
	}
}

static void	heredoc_func(t_redir *heredoc)
{
	char	*filename;
	int		filefd;
	int		backup_fd;

	hd_file(&filename, &filefd);
	backup_fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_handler);
	write_heredoc(heredoc, filefd);
	signal(SIGINT, SIG_IGN);
	dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
	close(filefd);
	free(heredoc->filename);
	heredoc->filename = filename;
}

void	exe_heredocs(t_cmd *cmd)
{
	t_token_type	type;
	int				i;

	i = 0;
	while (cmd->redirs[i].filename)
	{
		type = cmd->redirs[i].type;
		if (type == T_HEREDOC)
		{
			heredoc_func(&cmd->redirs[i]);
			if (sh_s()->exit_status == 700)
				break ;
		}
		i++;
	}
}
