/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:48 by adores            #+#    #+#             */
/*   Updated: 2026/03/18 15:47:12 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

static void	hd_file(char **name, int *num)
{
	char	*fileno;

	*num = 0;
	while (true)
	{
		fileno = ft_itoa(*num);
		*name = ft_strjoin("minishell-heredoc-", fileno);
		free(fileno);
		if (!*name)
			err_and_exit("malloc", "Allocation Error", 1, false);
		if (access(*name, F_OK) == -1)
		{
			*num = open(*name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*num == -1)
			{
				free(*name);
				err_and_exit("heredoc", "open", 1, true);
			}
			break ;
		}
		else
			*num += 1;
		free(*name);
	}
}

void	heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	sh_s()->exit_status = 130;
	close(STDIN_FILENO);
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
		if(!line && sh_s()->exit_status == 130)
			return ;
		else if (!line)
			return (heredoc_eof_warning(heredoc->filename));
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
	char	*filename;
	int		filenum;
	int		backup_fd;

	hd_file(&filename, &filenum);
	backup_fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_handler);
	write_heredoc(heredoc, filenum);
	dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
	
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
