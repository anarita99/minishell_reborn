/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:32 by adores            #+#    #+#             */
/*   Updated: 2026/03/23 16:12:22 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "shared.h"
# include "parser.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

// src/execution/builtins/env.c
void	set_env_var(char *key, char *value);
int		add_env_var(t_env **head, char *env);
t_env	*init_env(void);
int		env_builtin();


// src/execution/builtins/env_utils.c

int		env_lstsize(t_env *lst);
void	env_add_back(t_env **lst, t_env *node);
t_env	*env_new_node(char *key, char *value);
char	*get_env_value(t_env *env_list, char *key);
t_env	*get_env_node(t_env *env_list, char *key);

char	**envlist_to_char(t_env *env_list);

char	*path_to_execute(char *cmd);
void	execute_ext(t_cmd	*cmd);
void	free_execve(char **envp, char *full_path, char *cmd);

int		exe_all_heredocs(t_list *input);
void	clean_pipeline(int prev_read);
/*

** src/execution/exec.c

int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2]);
void	execute_command(char **args, char *envp[]);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		exe_builtin(char **args, t_shell *shell);*/


// src/execution/builtins/.c

int		echo_builtin(char **args);
int 	cd_builtin (char **args);
int		pwd_builtin(void);
int		exit_builtin(char **args);
int		env_builtin(void);
int		unset_builtin(char **args);
int		export_builtin(char **args);
int		is_builtin(char **args);
void	exe_builtin(t_cmd *cmd);
int		run_builtin(char **args);
void	print_sorted_env(void);

//src/execution/utils.c

void	report_err(char *context, char *detail, bool err);
void	exitclean(unsigned char exit_code);
void	err_and_exit(char *scope, char *msg, int exit_code, bool err);
void	free_node(t_env *node);
void	free_env_list(t_env *head);
void	free_arr(char **str);

void	executor(void);
int		setup_fds(t_cmd *input, int *og_fd, bool save);
void	overwrite_std(int *fd);
void	exe_heredocs(t_cmd *cmd);
void	exe_pipeline(int input_size);

void	setup_signals(void);
void	executor_signals(void);
void	handle_wait_status(int w_status);
void	child_signals(void);

#endif