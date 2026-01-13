/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:15:33 by adores & mi       #+#    #+#             */
/*   Updated: 2025/12/04 16:30:34 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*criar um ficheiro */
//open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

char *parse_outfiles(t_input *input)
{
	int i;
	char *name;

	i = 0;
	while(input->outfiles[i].filename) //ultimo filename é null
	{
		name = input->outfiles[i].filename;
		if(access(name, F_OK) == -1 || access(name, W_OK) == 0)
		{
			if(input->outfiles->mode == REDOUT)
				open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if(input->outfiles->mode == APPEND)
				open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			return (NULL); //mudar depois
		i++;
	}
	return (name);
}

char *parse_infiles(t_input *input)
{
	int i;
	char *name;

	i = 0;
	while(input->infiles[i].filename) //ultimo filename é null
	{
		name = input->infiles[i].filename;
		if(access(name, R_OK) == -1)
			return (NULL);     //pode ser necessario mudar
		i++;
	}
	return (name);
}


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
}