/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:15:33 by adores & mi       #+#    #+#             */
/*   Updated: 2025/11/24 16:48:20 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

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

void heredoc_func(t_file *heredoc)
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
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(heredoc->filename);
	heredoc->filename = filename;
	close(fd);
}

int main(void)
{
	t_file heredoc;
	heredoc.filename = ft_strdup("EOF");
	heredoc_func(&heredoc);
	return(0);
}