/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:08:31 by leramos-          #+#    #+#             */
/*   Updated: 2025/04/21 15:48:21 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static void	handle_whitespace(const char *nptr, size_t *i)
{
	while (ft_iswhitespace(nptr[*i]))
		(*i)++;
}

static int	handle_sign(const char *nptr, size_t *i)
{
	int	is_negative;

	is_negative = (nptr[*i] == '-');
	if (nptr[*i] == '+' || nptr[*i] == '-')
		(*i)++;
	return (is_negative);
}

static unsigned long
	handle_number(const char *nptr, size_t *i, int is_negative)
{
	unsigned long	number;

	number = 0;
	while (ft_isdigit(nptr[*i]))
	{
		number = (number * 10) + (nptr[*i] - '0');
		(*i)++;
	}
	if (is_negative)
		number = -number;
	return (number);
}

int	ft_atoi(const char *nptr)
{
	size_t			i;
	unsigned long	number;
	int				is_negative;

	i = 0;
	handle_whitespace(nptr, &i);
	is_negative = handle_sign(nptr, &i);
	number = handle_number(nptr, &i, is_negative);
	return ((int)(number));
}
