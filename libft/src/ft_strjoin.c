/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:04:34 by leramos-          #+#    #+#             */
/*   Updated: 2025/04/14 11:04:34 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	buffer_size;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	buffer_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(buffer_size);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, buffer_size);
	ft_strlcat(dst, s2, buffer_size);
	return (dst);
}
