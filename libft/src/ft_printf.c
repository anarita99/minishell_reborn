/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:57:18 by leramos-          #+#    #+#             */
/*   Updated: 2025/06/24 14:17:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	list;
	size_t	i;
	int		printed_chars;

	if (!s || (s[0] == '%' && s[1] == '\0'))
		return (-1);
	va_start(list, s);
	printed_chars = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (!is_valid_specifier(s[i++]))
				return (0);
			printed_chars += convert_and_write(s[i], &list);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			printed_chars++;
		}
		i++;
	}
	return (va_end(list), printed_chars);
}
