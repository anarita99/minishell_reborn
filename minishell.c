/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:18 by adores & mi       #+#    #+#             */
/*   Updated: 2026/02/03 18:56:37 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	free_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int main(void)
{
	char		*input;
	t_shell		shell;
	char **args;
	//t_list *list;
	t_cmd	*cmd;
	//pid_t pid;
	//char **envp;

	shell.env_list = init_env();
	shell.last_exit_status = 0;
	while (1)
	{
		input = readline("minishell > ");
		if (!input || !input[0])
		{
			free_env_list(shell.env_list);
			exit(0);
		}
		else
			add_history(input);
		args = ft_split(input, ' ');
		if (!ft_strncmp(args[0], "exit", 5))
		{
			exit_builtin(args);
		}
		else if (!ft_strncmp(args[0], "env", 4))
		{
			env_builtin();
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "echo", 5))
		{
		 	echo_builtin(args);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "unset", 6))
		{
		 	unset_builtin(args);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "export", 7))
		{
		 	export_builtin(args);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "pwd", 4))
		{
			pwd_builtin();
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "cd", 3))
		{
			cd_builtin(args);
			free_arr(args);
		}
		else
		{
			t_list *list;
			char *path;
			cmd = malloc(sizeof(t_cmd));
			if(!cmd)
				return (1);
			cmd->argv = args;
			cmd->redirs = NULL;
			list = ft_lstnew(cmd);
			//is_executable(args[0]);
			path = is_executable(cmd->argv[0]);
			printf("%s\n", path);
			//execve(path, cmd->argv, envp);
			free(cmd);
			free(list);
			free_arr(args);
		}
			
		/* else if (!ft_strncmp(args[0], "clear", 6))
		{
			pid = fork();
			if (pid == 0)
			{
				envp = env_list_to_char(env_list);
				if (execve("/usr/bin/clear", args, envp))
				{
					free_arr(args);
					free_arr(envp);
					term_env(env_list);
					exit(1);
				}
			}
			else
			{
				waitpid(pid, NULL, 0);
				free_arr(args);
			}
		} */
	}
	return 0;
}