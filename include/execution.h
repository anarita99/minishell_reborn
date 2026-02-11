/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:32 by adores            #+#    #+#             */
/*   Updated: 2026/02/11 16:09:37 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#  define EXECUTION_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <sysexits.h>
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef enum e_token
{
	REDIN, // <
	REDOUT, // >
	HDOC, // <<
	APPEND, // >>
}	t_token;

//shell struct
typedef struct s_shell
{
	int		exit_status;
	t_env	*env_list;
	t_list	*input_list;
	char	*cmd_line;
}	t_shell;

typedef struct		s_redir
{
	int				type;      // REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char			*filename; // "output.txt"
	bool			quoted;
}					t_redir;

typedef struct		s_cmd
{
	char			**argv;    // ["ls", "-l"]
	t_redir			*redirs;
}					t_cmd;


// srcs/execute/builtins/env.c
void	set_env_var(char *key, char *value);
int		add_env_var(t_env **head, char *env);
t_env	*init_env(void);
int		env_builtin();


// src/execute/builtins/env_functions.c

int		env_lstsize(t_env *lst);
void	env_add_back(t_env **lst, t_env *node);
t_env	*env_new_node(char *key, char *value);
char	*get_env_value(t_env *env_list, char *key);
t_env	*get_env_node(t_env *env_list, char *key);

char	**envlist_to_char(t_env *env_list);

char	*path_to_execute(char *cmd);
void	execute_ext(t_cmd	*cmd);
/*

** srcs/exec/exec.c

int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2]);
void	execute_command(char **args, char *envp[]);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		exe_builtin(char **args, t_shell *shell);*/


// src/execute/builtins/.c

int		echo_builtin(char **args);
int 	cd_builtin (char **args);
int		pwd_builtin();
int		exit_builtin(char **args);
int		env_builtin();
int		unset_builtin(char **args);
int		export_builtin(char **args);
int		is_builtin(char **args);

//src/execute/utils.c
void	print_err(char *context, char *detail, bool err);
void	exitclean(unsigned char exit_code);
void	error_exit(char *context, char *detail, int exit_code, bool err);
void	free_node(t_env *node);
void	free_env_list(t_env *head);
void	free_arr(char **str);

t_shell	*sh_s(void);

#endif