/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:04:18 by adores            #+#    #+#             */
/*   Updated: 2026/02/23 14:22:16 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exe_commands(t_cmd *input)
{
	char	*path;
	char	**env;

	if (setup_fds(input, NULL, false))
		exitclean(1);
	if (is_builtin(&input->argv[0]))
		exitclean(run_builtin(input->argv));
	else
	{
		path = path_to_execute(input->argv[0]);
		env = envlist_to_char(sh_s()->env_list);
		if (!env)
			return(free(path), error_exit("malloc", "allocation error", 1, false));
		if (execve(path, input->argv, env))
			free_execve(env, path, input->argv[0]);
	}
}

static void	setup_child(int i, int input_size)
{
	//signal(SIGINT, SIG_DFL);
	//signal(SIGQUIT, SIG_DFL);
	sh_s()->is_child = true;
	if (sh_s()->prev_read != -1)
	{
		dup2(sh_s()->prev_read, STDIN_FILENO);
		close(sh_s()->prev_read);
	}
	if (i < input_size - 1)
	{
		close(sh_s()->pipe_fds[0]);
		dup2(sh_s()->pipe_fds[1], STDOUT_FILENO);
		close(sh_s()->pipe_fds[1]);
	}
}

static void	execute_and_reset(t_list *current, int i, int input_size)
{
	if (sh_s()->pids[i] == 0)
	{
		setup_child(i, input_size);
		exe_commands((t_cmd *)current->content);
	}
	if (sh_s()->prev_read != -1)
		close(sh_s()->prev_read);
	if (i < input_size - 1)
	{
		close(sh_s()->pipe_fds[1]);
		sh_s()->prev_read = sh_s()->pipe_fds[0];
	}
}

bool	execute_all_hds(t_list *input)
{
	t_list	*current;

	current = input;
	while (current)
	{
		exe_heredocs((t_cmd *)current->content);
		/* if (msh()->hdoc_stop)
		{
			free(msh()->pids);
			msh()->pids = NULL;
			return (false);
		} */
		current = current->next;
	}
	return (true);
}

void	clean_failed_pipeline(int prev_read)
{
	int	i;
	int	w_status;

	i = 0;
	print_err(NULL, "pipe", true);
	while (sh_s()->pids[i] > 0)
	{
		waitpid(sh_s()->pids[i], &w_status, 0);
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	sh_s()->exit_status = 1;
	free(sh_s()->pids);
	sh_s()->pids = NULL;
}

void	exe_pipeline(int input_size)
{
	t_list	*curr;
	int		i;

	sh_s()->pids = malloc(sizeof(pid_t) * input_size);
	curr = sh_s()->input_list;
	if(!sh_s()->pids)
		error_exit("malloc", "allocation error", 1, false);
	if (!execute_all_hds(curr))
		return ;
	i = 0;
	while(curr)
	{
		if ((i < input_size - 1) && (pipe(sh_s()->pipe_fds) == -1))
			return (clean_failed_pipeline(sh_s()->prev_read));
		sh_s()->pids[i] = fork();
		execute_and_reset(curr, i, input_size);
		curr = curr->next;
		i++;
	}
}
