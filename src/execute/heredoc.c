/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:48 by adores            #+#    #+#             */
/*   Updated: 2026/02/23 11:12:08 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

static void	create_tmp_file(char **filename, int *filenum)
{
	char	*fileno;

	*filenum = 0;
	while (true)
	{
		fileno = ft_itoa(*filenum);
		*filename = ft_strjoin("minishell-heredoc-", fileno);
		free(fileno);
		if (!*filename)
			error_exit("malloc", "Allocation Error", 1, false);
		if (access(*filename, F_OK) == -1)
		{
			*filenum = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*filenum == -1)
			{
				free(*filename);
				error_exit("heredoc", "open", 1, true);
			}
			break ;
		}
		else
			*filenum += 1;
		free(*filename);
	}
}

void	print_hd_error(char *filename)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd("')", 2);
}

static void	write_heredoc(t_redir *heredoc, int filefd)
{
	char	*line;
	//char	*expanded;

	while (true)
	{
		line = readline(">");
		/* if (msh()->hdoc_stop)
			return ; */
		if (!line)
			return (print_hd_error(heredoc->filename));
		if (ft_strcmp(line, heredoc->filename) == 0)
			return (free(line));
		/* if (!heredoc->quoted)
		{
			//expanded = hdoc_expand_arg(line);
			ft_putendl_fd(expanded, filefd);
			free(expanded);
		} */
		//else
		ft_putendl_fd(line, filefd);
		free(line);
	}
}

static void	heredoc_func(t_redir *heredoc)
{
	char *filename;
	int	filenum;

	create_tmp_file(&filename, &filenum);
	write_heredoc(heredoc, filenum);
	close(filenum);
	free(heredoc->filename);
	heredoc->filename = filename;
	
}

void	exe_heredocs(t_cmd *cmd)
{
	t_token_type	type;
	int				i;
	//int				stdin_backup;

	i = 0;
	//stdin_backup = dup(STDIN_FILENO);
	while (cmd->redirs[i].filename)
	{
		type = cmd->redirs[i].type;
		if (type == T_HEREDOC)
			heredoc_func(&cmd->redirs[i]);
		/* if (msh()->hdoc_stop)
		{
			dup2(stdin_backup, STDIN_FILENO);
			break ;
		} */
		i++;
	}
	//close(stdin_backup);
}
