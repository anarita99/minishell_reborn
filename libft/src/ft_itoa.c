/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:46:02 by leramos-          #+#    #+#             */
/*   Updated: 2025/04/21 13:38:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_longlen(long n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	str_len;
	char	*str;
	long	num;
	int		i;
	int		is_negative;

	num = n;
	is_negative = (num < 0);
	if (is_negative)
		num = -num;
	str_len = ft_longlen(num) + is_negative;
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	i = str_len - 1;
	while (i >= 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	if (is_negative)
		str[0] = '-';
	str[str_len] = '\0';
	return (str);
}
