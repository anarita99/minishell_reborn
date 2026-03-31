/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:43:56 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/30 13:36:37 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words_ws(char const *str)
{
	size_t	count;

	if (!*str)
		return (0);
	count = 0;
	while (*str)
	{
		while (ft_iswhitespace(*str))
			str++;
		if (*str)
			count++;
		while (*str && !ft_iswhitespace(*str))
			str++;
	}
	return (count);
}

static char	**fill_array_ws(char **array, char const *str)
{
	size_t	i;
	size_t	str_len;
	char	*end;

	i = 0;
	while (*str)
	{
		while (ft_iswhitespace(*str))
			str++;
		if (*str)
		{
			end = (char *)str;
			while (*end && !ft_iswhitespace(*end))
				end++;
			str_len = end - str;
			array[i] = ft_substr(str, 0, str_len);
			str += str_len;
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split_ws(char const *s)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((count_words_ws(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (fill_array_ws(array, s));
}
