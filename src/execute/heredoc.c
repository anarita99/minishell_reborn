/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:17:48 by adores            #+#    #+#             */
/*   Updated: 2026/02/12 16:54:12 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

bool parse_redirects(t_cmd *cmd, char **infile, char **outfile);

int	setup_fds(t_cmd *input, int *og_fd, bool save);
/* {
	int	new_fd[2];
	int	err;

	err = 0;
	if (save)
		save_og_fds(og_fd);
	if (input->infiles->filename)
	{
		parse_infiles(input, &err, &new_fd[0]);
		if (err)
			return (err);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		parse_outfiles(input, &new_fd[1], &err);
		if (err)
			return (err);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	return (err);
} */

char	*create_temp_file(void)
{
	char	*name;
	int		i;
	char	*numstr;

	i = 0;
	while(1)
	{
		numstr = ft_itoa(i);
		if(!numstr)
			return (NULL); //malloc error
		name = ft_strjoin("minishell-heredoc-", numstr);
		free(numstr);
		if(!name)
			return (NULL);
		if(access(name, F_OK) == 0)
		{
			free(name);
			i++;
		}
		else
			break;
	}
	return(name);
}

void heredoc_func(t_redir *heredoc)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = create_temp_file();
	if(!filename)
		return ; //malloc error
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while(1)
	{
		line = readline(">");
		if(!line || (ft_strcmp(heredoc->filename, line) == 0))
		{
			free(line);
			break;
		}
		//chamar funçao de expansao
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(heredoc->filename);
	heredoc->filename = filename;
	close(fd);
}
/*
int main(void)
{
	t_input input;
	input.infiles = malloc(sizeof(t_file) * 3);
	
	input.infiles[0].filename = "file.txt";
	input.infiles[1].filename = "file2.txt";
	input.infiles[2].filename = NULL;
	char *function = parse_infiles(&input);
	if (function != NULL)
		printf("%s\n",parse_infiles(&input));
	else
		printf("null\n");
	return(0);
}*/