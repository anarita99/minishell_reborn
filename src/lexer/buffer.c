/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:46:43 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 15:53:41 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_buffer	*create_buffer(char *input)
{
	t_buffer	*buffer;

	buffer = malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	buffer->size = ft_strlen(input);
	buffer->data = malloc(sizeof(char) * buffer->size + 1);
	if (!buffer->data)
		return (NULL);
	buffer->data[buffer->size] = '\0';
	buffer->len = 0;
	return (buffer);
}

// TODO
void	free_buffer(void)
{
	;
}

void add_char_to_buffer(t_buffer *buffer, char c)
{
	if (buffer->len == buffer->size)
		return ;
	buffer->data[buffer->len] = c;
	buffer->len++;
	buffer->data[buffer->len] = '\0';
}

void	reset_buffer(t_buffer *buffer)
{
	buffer->len = 0;
	buffer->data[0] = '\0';
}
