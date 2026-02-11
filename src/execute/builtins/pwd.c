/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:18:01 by adores            #+#    #+#             */
/*   Updated: 2026/02/11 16:35:21 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/execution.h"

int	pwd_builtin()
{
	char	*cwd;

	sh_s()->exit_status = 0;
	cwd = getcwd(NULL, 0); //se o buffer for null ele aloca um array com o tamanho necessário
	if (cwd == NULL)
	{
		cwd = get_env_value(sh_s()->env_list, "PWD");
		if (cwd == NULL)
		{
			ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			sh_s()->exit_status = 1;
			return (1);
		}
		else
			printf("%s\n", cwd);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
