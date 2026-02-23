/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:05:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/23 11:40:11 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


// Project Modules
# include "shared.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"

//shell struct
typedef struct s_shell
{
	int		exit_status;
	bool	is_child;
	int		prev_read;
	t_env	*env_list;
	t_list	*input_list;
	char	*cmd_line;
	int		original_fds[2];
	int		pipe_fds[2];
	pid_t	*pids;
}	t_shell;

// Print Functions (Debug purposes)
void	print_tokens(t_token *head);
void	print_cmdlst(t_list *cmd_lst);

t_shell	*sh_s(void);

#endif