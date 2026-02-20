/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:12:16 by leramos-          #+#    #+#             */
/*   Updated: 2025/06/24 13:06:54 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// %c - Prints a single character (Example: a)
int	ft_printf_char(va_list *list)
{
	char	c;

	c = va_arg(*list, int);
	ft_putchar_fd(c, 1);
	return (1);
}

// %s - Prints a string (Example: sample)
int	ft_printf_string(va_list *list)
{
	char	*str;
	int		len;

	str = va_arg(*list, char *);
	if (str)
	{
		len = ft_strlen(str);
		ft_putstr_fd(str, 1);
	}
	else
	{
		len = 6;
		ft_putstr_fd("(null)", 1);
	}
	return (len);
}

// %p - Prints a void * pointer in Hexadecimal (Example: b8000000)
int	ft_printf_pointer(va_list *list)
{
	unsigned long long	n;
	int					len;

	n = (unsigned long long)va_arg(*list, void *);
	if (n == 0)
	{
		len = 5;
		ft_putstr_fd("(nil)", 1);
	}
	else
	{
		len = 2 + ft_nbrlen_unsigned(n, 16);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_unsigned(n, "0123456789abcdef");
	}
	return (len);
}

// %i / %d - Prints an integer in Base 10 (Example: 392)
int	ft_printf_integer(va_list *list)
{
	int	i;
	int	len;

	i = va_arg(*list, int);
	len = ft_nbrlen(i, 10);
	ft_putnbr_fd(i, 1);
	return (len);
}

// %u / %x / %X - Prints an unsigned integer with given base
int	ft_printf_unsigned_base(va_list *list, char *base, int base_len)
{
	unsigned int	i;
	int				len;

	i = va_arg(*list, unsigned int);
	len = ft_nbrlen_unsigned(i, base_len);
	ft_putnbr_base_unsigned(i, base);
	return (len);
}
