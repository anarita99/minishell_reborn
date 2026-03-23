/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:55:02 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 16:03:47 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_execve(char **envp, char *full_path, char *cmd)
{
	free_arr(envp);
	free(full_path);
	err_and_exit(NULL, cmd, 1, true);
}

void	execute_ext(t_cmd	*cmd)
{
	pid_t	pid;
	char	**envp;
	char	*full_path;
	int		w_status;

	pid = fork();
	if (pid == -1)
		return (sh_s()->exit_status = 1, report_err("fork", NULL, true));
	if (pid == 0)
	{
		child_signals();
		if (setup_fds(cmd, sh_s()->original_fds, false) == 1)
			exitclean(1);
		full_path = path_to_execute(cmd->argv[0]);
		envp = envlist_to_char(sh_s()->env_list);
		if (!envp)
			return (free(full_path), err_and_exit("malloc", \
"allocation error", 1, false));
		if (execve(full_path, cmd->argv, envp))
			free_execve(envp, full_path, cmd->argv[0]);
	}
	wait(&w_status);
	handle_wait_status(w_status);
}
