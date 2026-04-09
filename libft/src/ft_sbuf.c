/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:07 by codespace         #+#    #+#             */
/*   Updated: 2026/04/09 22:44:02 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sbuf	*sbuf_init(size_t cap)
{
	t_sbuf	*b;

	b = malloc(sizeof(t_sbuf));
	if (!b)
		return (NULL);
	b->data = malloc(cap);
	if (!b->data)
		return (free(b), NULL);
	b->data[0] = '\0';
	b->cap = cap;
	b->len = 0;
	return (b);
}

void	sbuf_free(t_sbuf *b)
{
	free(b->data);
	free(b);
}

void	sbuf_reset(t_sbuf *b)
{
	b->data[0] = '\0';
	b->len = 0;
}

int	sbuf_push_char(t_sbuf *b, char c)
{
	char	*new_data;
	size_t	new_cap;

	if (b->len + 2 > b->cap)
	{
		new_cap = b->cap;
		while (new_cap < b->len + 2)
			new_cap *= 2;
		new_data = malloc(new_cap);
		if (!new_data)
			return (0);
		ft_memcpy(new_data, b->data, b->len + 1);
		free(b->data);
		b->data = new_data;
		b->cap = new_cap;
	}
	b->data[b->len] = c;
	b->len++;
	b->data[b->len] = '\0';
	return (1);
}

int	sbuf_push_str(t_sbuf *b, const char *str)
{
	size_t	str_len;
	char	*new_data;
	size_t	new_cap;

	if (!str)
		return (0);
	str_len = ft_strlen(str);
	if (b->len + str_len + 1 > b->cap)
	{
		new_cap = b->cap;
		while (new_cap < b->len + str_len + 1)
			new_cap *= 2;
		new_data = malloc(new_cap);
		if (!new_data)
			return (0);
		ft_memcpy(new_data, b->data, b->len + 1);
		free(b->data);
		b->data = new_data;
		b->cap = new_cap;
	}
	ft_memcpy(b->data + b->len, str, str_len + 1);
	b->len += str_len;
	return (1);
}
