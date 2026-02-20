/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:56:28 by leramos-          #+#    #+#             */
/*   Updated: 2025/10/27 12:08:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

// Main
int		ft_printf(const char *s, ...);

// Utils
int		is_valid_specifier(char c);
int		convert_and_write(char specifier, va_list *list);

// Specifiers
int		ft_printf_char(va_list *list);
int		ft_printf_string(va_list *list);
int		ft_printf_pointer(va_list *list);
int		ft_printf_integer(va_list *list);
int		ft_printf_unsigned_base(va_list *list, char *base, int base_len);

// Output
void	ft_putnbr_base(int nbr, char *base);
void	ft_putnbr_base_unsigned(unsigned long long n, char *base);
size_t	ft_nbrlen(int n, int base_len);
size_t	ft_nbrlen_unsigned(unsigned long long n, int base_len);

#endif