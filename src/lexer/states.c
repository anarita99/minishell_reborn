/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/28 17:20:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_word(int *state, char c, t_sbuf *buf)
{
	sbuf_push_char(buf, c);
	if (c == '\'')
		*state = STATE_IN_SQUOTE;
	else if (c == '\"')
		*state = STATE_IN_DQUOTE;
	return (T_NONE);
}

static int	handle_operator(char c, t_sbuf *buf, int *consumed, char c_next)
{
	sbuf_push_char(buf, c);
	if (c == '|')
		return (T_PIPE);
	if (c_next == c)
	{
		sbuf_push_char(buf, c);
		*consumed = 2;
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

int	state_normal(int *state, char c, t_sbuf *buf, int *consumed, char c_next)
{
	if (is_word(c))
		return (handle_word(state, c, buf));
	if (buf->len > 0)
	{
		*consumed = 0;
		return (T_WORD);
	}
	if (is_operator(c))
		return (handle_operator(c, buf, consumed, c_next));
	return (T_NONE);
}

int	state_quote(int *state, char c, t_sbuf *buf)
{
	sbuf_push_char(buf, c);
	if ((*state == STATE_IN_SQUOTE && c == '\'') || (*state == STATE_IN_DQUOTE && c == '\"'))
		*state = STATE_NORMAL;
    return (T_NONE);
}
