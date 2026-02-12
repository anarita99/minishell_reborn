/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:06:58 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/12 16:37:24 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shared.h"
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;		// REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char			*filename;	// "output.txt"
	bool			quoted;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;		// ["ls", "-l", NULL]
	t_redir			*redirs;
}					t_cmd;

// Arguments
char	**get_argv(t_token *current_token);

// Redirects
t_redir	*get_redirs(t_token *current_token);

// Commands
t_cmd	*get_next_cmd(t_token *current_token);
void	del_cmd(void *cmd_ptr);

// Main parser function
t_list	*parser(t_token *head);

#endif
