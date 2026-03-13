/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:42 by leramos-          #+#    #+#             */
/*   Updated: 2025/06/20 14:31:54 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_base_valid(char *base)
{
	int	i;
	int	j;

	if (!base[0] || !base[1])
		return (0);
	i = 0;
	j = 0;
	while (base[i])
	{
		j = 0;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (j < i)
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int			base_size;
	long int	n;

	if (!is_base_valid(base))
		return ;
	n = nbr;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
	}
	base_size = ft_strlen(base);
	if (n >= base_size)
		ft_putnbr_base(n / base_size, base);
	ft_putchar_fd(base[n % base_size], 1);
}

void	ft_putnbr_base_unsigned(unsigned long long n, char *base)
{
	size_t	base_size;

	if (!is_base_valid(base))
		return ;
	base_size = ft_strlen(base);
	if (n >= base_size)
		ft_putnbr_base_unsigned(n / base_size, base);
	ft_putchar_fd(base[n % base_size], 1);
}

size_t	ft_nbrlen(int n, int base_len)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

size_t	ft_nbrlen_unsigned(unsigned long long n, int base_len)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}
