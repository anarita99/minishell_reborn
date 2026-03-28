/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:06:58 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/28 17:18:12 by leramos-         ###   ########.fr       */
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
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef enum e_str_state
{
	STATE_NORMAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE,
	STATE_IN_OP
}	t_str_state;

typedef enum e_char_type
{
	C_DELIMITER,
	C_WORD,
	C_SQUOTE,
	C_DQUOTE,
	C_OPERATOR
}	t_char_type;

// Token

t_token	*create_token(t_token_type type, char *value);
void	add_token_to_list(t_token **head, t_token **tail, t_token *token);
void	free_tokens(t_token **head);
int		is_token_operator(t_token *token);
void 	print_syntax_error(char *token_value);
int		validate_tokens(t_token *head);

// Types

int		is_word(char c);
int		is_operator(char c);
t_token	*create_word(char *input, int start_idx, int end_idx);
t_token	*create_operator(t_token_type type, char *str);

// States
int	state_normal(int *state, char c, t_sbuf *buf, int *consumed, char c_next);
int	state_quote(int *state, char c, t_sbuf *buf);

t_token	*lexer(char *input);

#endif