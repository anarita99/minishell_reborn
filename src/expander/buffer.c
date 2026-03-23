/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:07 by codespace         #+#    #+#             */
/*   Updated: 2026/03/23 17:14:53 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_sbuf *sbuf_init(size_t initial_cap)
{
	t_sbuf	*buf;

	buf = malloc(sizeof(t_sbuf));
	if (!buf)
		return (NULL);
	buf->data = malloc(initial_cap);
	if (!buf->data)
	{
		free(buf);
		return (NULL);
	}
	buf->len = 0;
	buf->size = initial_cap;
	buf->data[0] = '\0';
	return (buf);
}

void	free_sbuf(t_sbuf *buf)
{
	free(buf->data);
	free(buf);
}

void	sbuf_reset(t_sbuf *buf)
{
	buf->data[0] = '\0';
	buf->len = 0;
}

static int sbuf_reserve(t_sbuf *buf, size_t need)
{
	char    *new_data;
	size_t  new_cap;

	if (need <= buf->size)
		return (1);
	new_cap = buf->size;
	while (new_cap < need)
		new_cap *= 2;
	new_data = malloc(new_cap);
	if (!new_data)
		return (0);
	memcpy(new_data, buf->data, buf->len + 1);
	free(buf->data);
	buf->data = new_data;
	buf->size = new_cap;
	return (1);
}

int sbuf_push_char(t_sbuf *buf, char c)
{
	if (!sbuf_reserve(buf, buf->len + 2))
		return (0);
	buf->data[buf->len++] = c;
	buf->data[buf->len] = '\0';
	return (1);
}

int sbuf_push_str(t_sbuf *buf, const char *str)
{
	if (!str)
		return (0);
	size_t add = strlen(str);
	if (!sbuf_reserve(buf, buf->len + add + 1))
		return (0);
	ft_memcpy(buf->data + buf->len, str, add + 1);
	buf->len += add;
	return (1);
}
