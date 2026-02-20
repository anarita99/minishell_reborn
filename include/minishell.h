/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:05:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/20 14:31:00 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


// Project Modules
# include "shared.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"

// Shell Structure
typedef struct s_shell
{
	int		exit_status;
	t_env	*env_list;
	t_list	*input_list;
	char	*cmd_line;
	int		original_fds[2];
}	t_shell;

// Print Functions (Debug purposes)
void	print_tokens(t_token *head);
void	print_cmdlst(t_list *cmd_lst);

// Shell Singleton
t_shell	*sh_s(void);

#endif