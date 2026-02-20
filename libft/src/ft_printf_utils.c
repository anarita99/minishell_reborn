/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:17:00 by leramos-          #+#    #+#             */
/*   Updated: 2025/06/24 13:04:44 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_valid_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

int	convert_and_write(char specifier, va_list *list)
{
	if (specifier == 'c')
		return (ft_printf_char(list));
	else if (specifier == 's')
		return (ft_printf_string(list));
	else if (specifier == 'p')
		return (ft_printf_pointer(list));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_printf_integer(list));
	else if (specifier == 'u')
		return (ft_printf_unsigned_base(list, "0123456789", 10));
	else if (specifier == 'x')
		return (ft_printf_unsigned_base(list, "0123456789abcdef", 16));
	else if (specifier == 'X')
		return (ft_printf_unsigned_base(list, "0123456789ABCDEF", 16));
	else if (specifier == '%')
		return (ft_putchar_fd('%', 1), 1);
	else
		return (0);
}
