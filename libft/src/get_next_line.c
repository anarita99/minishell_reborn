/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:35:59 by leramos-          #+#    #+#             */
/*   Updated: 2025/10/27 12:05:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*stash;

	stash = init_stash_from_leftover(&leftover);
	if (!stash)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (free(stash), NULL);
	line = extract(stash, &leftover);
	free(stash);
	if (!line || line[0] == '\0')
	{
		free(line);
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	return (line);
}
