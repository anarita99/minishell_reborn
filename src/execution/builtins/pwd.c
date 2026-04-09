/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:18:01 by adores            #+#    #+#             */
/*   Updated: 2026/04/09 22:52:05 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	*cwd;

	sh_s()->exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = get_env_value(sh_s()->env_list, "PWD");
		if (cwd == NULL)
		{
			ft_putstr_fd("pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 2);
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
