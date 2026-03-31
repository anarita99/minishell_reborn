/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:04:18 by adores            #+#    #+#             */
/*   Updated: 2026/03/31 10:46:11 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_path_cmd(t_cmd *input)
{
	char	*path;
	char	**env;

	path = path_to_execute(input->argv[0]);
	env = envlist_to_char(sh_s()->env_list);
	if (!env)
		return (free(path), err_and_exit("malloc", "allocation error", \
1, false));
	if (execve(path, input->argv, env))
		free_execve(env, path, input->argv[0]);
}

static void	exe_commands(t_cmd *input)
{
	if (setup_fds(input, NULL, false))
		exitclean(1);
	if (is_builtin(&input->argv[0]))
		exitclean(run_builtin(input->argv));
	else
		exec_path_cmd(input);
}

static void	pipeline_proc(t_list *current, int i, int input_size)
{
	if (sh_s()->pids[i] == 0)
	{
		child_pipes(i, input_size);
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

static bool	init_pipeline(int input_size)
{
	sh_s()->pids = ft_calloc(input_size, sizeof(pid_t));
	if (!sh_s()->pids)
		return (err_and_exit("malloc", "allocation error", 1, false), false);
	if (!exe_all_heredocs(sh_s()->input_list))
		return (false);
	return (true);
}

void	exe_pipeline(int input_size)
{
	t_list	*curr;
	int		i;

	if (!init_pipeline(input_size))
		return ;
	curr = sh_s()->input_list;
	i = 0;
	while (curr)
	{
		if ((i < input_size - 1) && (pipe(sh_s()->pipe_fds) == -1))
			return (clean_pipeline(sh_s()->prev_read));
		sh_s()->pids[i] = fork();
		pipeline_proc(curr, i, input_size);
		curr = curr->next;
		i++;
	}
}
