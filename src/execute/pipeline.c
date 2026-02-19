/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:04:18 by adores            #+#    #+#             */
/*   Updated: 2026/02/19 17:49:48 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	wait_children(void)
{
} */

static void	exe_commands(t_cmd *input)
{
	char	*path;
	char	**env;

	if (setup_fds(input, NULL, false))
		exitclean(1);
	if (is_builtin(input->argv[0]))
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

void	exe_pipeline(int input_size)
{
	t_list	*curr;
	int		i;

	sh_s()->pids = malloc(sizeof(pid_t) * input_size);
	i = 0;
	curr = sh_s()->input_list;
	while(curr)
	{
		if ((i < input_size - 1) && (pipe(sh_s()->pipe_fds) == -1))
			return ; //clean_pipes
		sh_s()->pids[i] = fork(); // fork error
		if (sh_s()->pids[i] == 0)
			exe_commands((t_cmd *)curr->content);
		curr = curr->next;
		i++;
	}
}
