/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:31 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/31 15:47:00 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "shared.h"
# include "parser.h"
# include "lexer.h"
# include "execution.h"

typedef struct s_expander_ctx
{
	t_sbuf		*buf;
	t_env		*env_list;
	int			status;
	t_str_state	state;
	bool		keep_empty_word;
}	t_expander_ctx;

// Utils
char	*expand_heredoc(char *src, t_env *env_list, int status);
char	**convert_lst_to_argv(t_list *lst);
char	*convert_lst_to_str(t_list *lst);
int	    get_key_size(char *str, int i);
char    *get_value(t_env *env_list, int status, char *key);

// Scan word
t_list *expand_input(char *input, t_env *env_list, int status, bool is_heredoc);

// Main expander function
void	expander(t_list **commands, t_env *env_list, int status);

#endif
