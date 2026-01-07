/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/12/08 16:06:01 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "libft/libft.h"

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

typedef struct s_file
{
	char	*filename;
	t_token	mode;
	bool	quoted;
} t_file;

typedef struct s_input
{
	char	**argv;
	t_file	*infiles;
	t_file	*outfiles;
} t_input;

//shell struct
typedef struct s_shell
{
	int		last_exit_status;
	t_env	*env_list;
	t_list	*input_list;
	char	*cmd_line;
}	t_shell;


/*
** srcs/env/env.c
*/
int		add_env_var(t_env **head, char *env);
t_env	*init_env(void);
int		env_builtin(t_shell *shell);

/*
** srcs/env/env_functions.c
*/
int		env_lstsize(t_env *lst);
void	env_add_back(t_env **lst, t_env *node);
t_env	*env_new_node(char *key, char *value);
char	*get_env_value(t_env *env_list, char *key);
t_env	*get_env_node(t_env *env_list, char *key);
void	free_node(t_env *node);
void	free_env_list(t_env *head);
void	free_str_array(char **str);
void	set_env_var(t_env **env_list, char *key, char *value);


/*
** srcs/exec/exec.c

int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2]);
void	execute_command(char **args, char *envp[]);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		exe_builtin(char **args, t_shell *shell);*/

/*
** execution/builtins/.c
*/
int		echo_builtin(char **args, t_shell *shell);
int 	cd_builtin (t_shell *shell, char **args);
int		pwd_builtin(t_shell *shell);
int		exit_builtin(char **args, t_shell *shell);
void	malloc_error(t_env *env_list);
int		env_builtin(t_shell *shell);
int		unset_builtin(char **args, t_shell *shell);
int		export_builtin(char **args, t_shell *shell);
int		is_builtin(char **args);



#endif