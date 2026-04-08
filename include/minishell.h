/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:05:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 20:41:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Project Modules
# include "shared.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "execution.h"

// Shell Structure
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
void	print_tokenlst(t_list *token_list);
void	print_cmdlst(t_list *cmd_lst);

// Shell Singleton
t_shell	*sh_s(void);

#endif