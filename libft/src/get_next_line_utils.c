/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:04:32 by leramos-          #+#    #+#             */
/*   Updated: 2025/10/27 12:05:43 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*init_stash_from_leftover(char **leftover)
{
	char	*stash;

	if (*leftover)
	{
		stash = ft_strdup(*leftover);
		free(*leftover);
		*leftover = NULL;
	}
	else
		stash = ft_strdup("");
	return (stash);
}

char	*read_until_newline(int fd, char *stash)
{
	int		n_bytes;
	char	*buf;
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	n_bytes = 1;
	while (n_bytes > 0 && find_newline(stash) == -1)
	{
		n_bytes = read(fd, buf, BUFFER_SIZE);
		if (n_bytes <= 0)
			break ;
		buf[n_bytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		free(stash);
		stash = tmp;
	}
	free(buf);
	if (n_bytes < 0)
		return (free(stash), NULL);
	return (stash);
}

char	*extract(char *stash, char **leftover)
{
	char	*line;
	int		newline_pos;
	int		stash_len;
	int		leftover_len;
	int		line_len;

	newline_pos = find_newline(stash);
	stash_len = ft_strlen(stash);
	if (newline_pos != -1)
	{
		line_len = newline_pos + 1;
		leftover_len = stash_len - (newline_pos + 1);
		line = ft_substr(stash, 0, line_len);
		*leftover = ft_substr(stash, newline_pos + 1, leftover_len);
	}
	else
	{
		*leftover = NULL;
		if (stash_len > 0)
			line = ft_strdup(stash);
		else
			line = NULL;
	}
	return (line);
}
