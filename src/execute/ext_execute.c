/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:55:02 by adores            #+#    #+#             */
/*   Updated: 2026/02/05 17:39:22 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_execve(char **envp, char *full_path, char *cmd)
{
	free_arr(envp);
	free(full_path);
	error_exit(NULL, cmd, 1, true);
}

static void	wait_child(void)
{
	int	w_status;
	//int	sig;

	wait(&w_status);
	if (WIFEXITED(w_status))
		sh_s()->exit_status = WEXITSTATUS(w_status);
	else if (WIFSIGNALED(w_status))
	{
		//sig = WTERMSIG(w_status);
		//if (sig == SIGQUIT)
		//   ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		sh_s()->exit_status = 128;
	}
}

void	execute_ext(t_cmd	*cmd)
{
	pid_t	pid;
	char	**envp;
	char	*full_path;

	
	pid = fork();
	if(pid == -1)
		return (sh_s()->exit_status = 1, print_err("fork", NULL, true));
	if(pid == 0)
	{
		//setup_fds -- redir
		full_path = path_to_execute(cmd->argv[0]);
		envp = envlist_to_char(sh_s()->env_list);
		if (!envp)
			return(free(full_path), error_exit("malloc", "allocation error", 1, false));
		if(execve(full_path, cmd->argv, envp))
			free_execve(envp, full_path, cmd->argv[0]);
	}
	wait_child();
}

