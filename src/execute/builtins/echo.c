/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:13:37 by adores            #+#    #+#             */
/*   Updated: 2026/02/05 16:59:27 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "execution.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while(arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

int	echo_builtin(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		ft_putstr_fd(args[i], 1);
		if(args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if(newline == 1)
		ft_putstr_fd("\n", 1);
	sh_s()->exit_status = 0;
	return (0);
}
