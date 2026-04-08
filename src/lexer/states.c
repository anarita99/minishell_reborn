/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 20:09:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_type	handle_word(int *state, t_sbuf *buf, char c)
{
	sbuf_push_char(buf, c);
	if (c == '\'')
		*state = STATE_SQUOTE;
	else if (c == '\"')
		*state = STATE_DQUOTE;
	return (T_NONE);
}

static t_token_type	handle_operator(t_sbuf *buf, char c, char c_next)
{
	sbuf_push_char(buf, c);
	if (c == '|')
		return (T_PIPE);
	if (c_next == c)
	{
		sbuf_push_char(buf, c);
		if (c == '<')
			return (T_HEREDOC);
		else
			return (T_APPEND);
	}
	if (c == '<')
		return (T_REDIR_IN);
	else
		return (T_REDIR_OUT);
}

static t_token_type	state_normal(int *state, t_sbuf *buf, char c, char c_next)
{
	if (is_word(c))
		return (handle_word(state, buf, c));
	if (buf->len > 0)
		return (T_WORD);
	if (is_operator(c))
		return (handle_operator(buf, c, c_next));
	return (T_NONE);
}

static t_token_type	state_quote(int *state, t_sbuf *buf, char c)
{
	sbuf_push_char(buf, c);
	if ((*state == STATE_SQUOTE && c == '\'')
		|| (*state == STATE_DQUOTE && c == '\"'))
		*state = STATE_NORMAL;
	return (T_NONE);
}

t_token_type	state_machine(int *state, t_sbuf *buf, char c, char c_next)
{
	if (*state == STATE_NORMAL)
		return (state_normal(state, buf, c, c_next));
	else if (*state == STATE_SQUOTE || *state == STATE_DQUOTE)
		return (state_quote(state, buf, c));
	return (T_NONE);
}
