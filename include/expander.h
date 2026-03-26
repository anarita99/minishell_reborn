/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:31 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/26 14:59:58 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "shared.h"
# include "parser.h"
# include "lexer.h"
# include "execution.h"

typedef struct s_sbuf
{
	char   *data;
	size_t	size;	// size allocated
	size_t	len;	// current valid length
}   t_sbuf;

// Buffer
t_sbuf *sbuf_init(size_t initial_cap);
void	sbuf_reset(t_sbuf *buf);
void	free_sbuf(t_sbuf *buf);
int 	sbuf_push_char(t_sbuf *buf, char c);
int 	sbuf_push_str(t_sbuf *buf, const char *str);

// Utils
char	**convert_lst_to_argv(t_list *lst);
int     update_quote_state(t_str_state *state, char c);
int	    get_key_size(char *str, int i);
char    *get_value(t_env *env_list, int exit_status, char *key);

// Scan word
// char 	*expand_filename(char *input, t_env *env_list, int exit_status);
char *expand_filename(char *input, t_env *env_list, int exit_status, int (*update)(t_str_state *, char c));
void 	expand_str(t_list **expanded_words, char *input, t_env *env_list, int exit_status);

// Main expander function
void	expander(t_list **commands, t_env *env_list, int exit_status);

#endif
