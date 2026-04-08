/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:06:58 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 20:13:40 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shared.h"

typedef enum e_token_type
{
	T_NONE,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_str_state
{
	STATE_NORMAL,
	STATE_SQUOTE,
	STATE_DQUOTE
}	t_str_state;

// Token
void			del_token(void *token_ptr);
int				is_token_operator(t_token *token);
void			print_syntax_error(const char *token_value);
void			append_token_to_lst(t_list **lst, int token_type, t_sbuf *buf);

// Utils
bool			is_word(char c);
bool			is_operator(char c);
int				calc_consumed_chars(t_token_type token_type);

// States
t_token_type	state_machine(int *state, t_sbuf *buf, char c, char c_next);

// Validation
int				validate_tokens(t_list *token_list);

// Lexer
t_list			*lexer(const char *input);

#endif