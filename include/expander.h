/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:31 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/09 20:03:59 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "shared.h"
# include "parser.h"
# include "lexer.h"
# include "execution.h"

typedef enum e_expander_mode
{
	EXPAND_ARGV,
	EXPAND_REDIR,
	EXPAND_HEREDOC
}	t_expander_mode;

typedef struct s_expander_ctx
{
	t_sbuf			*buf;
	t_env			*env_list;
	int				status;
	t_str_state		state;
	t_expander_mode	mode;
	bool			keep_empty_word;
}	t_expander_ctx;

// Utils
char	*expand_heredoc(char *src);
char	**convert_lst_to_argv(t_list *lst);
char	*convert_lst_to_str(t_list *lst);
int		get_key_size(char *str, int i);
char	*get_value(char *key);

// Scan word
t_list	*expand_input(char *input, t_expander_mode mode);

// Main expander function
void	expander(t_list **commands);

#endif
