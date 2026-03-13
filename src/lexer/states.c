/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/03 16:30:55 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_word(int *state, char c, t_buffer *buffer)
{
	add_char_to_buffer(buffer, c);
	if (c == '\'')
		*state = STATE_IN_SQUOTE;
	else if (c == '\"')
		*state = STATE_IN_DQUOTE;
	return (T_NONE);
}

static int	handle_operator(char c, t_buffer *buffer, int *consumed, char c_next)
{
	add_char_to_buffer(buffer, c);
	if (c == '|')
		return (T_PIPE);
	if (c_next == c)
	{
		add_char_to_buffer(buffer, c);
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

int	state_normal(int *state, char c, t_buffer *buffer, int *consumed, char c_next)
{
	if (is_word(c))
		return (handle_word(state, c, buffer));
	if (buffer->len > 0)
	{
		*consumed = 0;
		return (T_WORD);
	}
	if (is_operator(c))
		return (handle_operator(c, buffer, consumed, c_next));
	return (T_NONE);
}

int	state_quote(int *state, char c, t_buffer *buffer)
{
	add_char_to_buffer(buffer, c);
	if ((*state == STATE_IN_SQUOTE && c == '\'') || (*state == STATE_IN_DQUOTE && c == '\"'))
		*state = STATE_NORMAL;
    return (T_NONE);
}
