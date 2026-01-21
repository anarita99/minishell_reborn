/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 15:55:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	state_normal(int *state, char c, int c_type, t_buffer *buffer, int *consumed, char c_next)
{
	if (c_type == C_DELIMITER)
	{
		if (buffer->len > 0)
			return (T_WORD);
	}
	else if (c_type == C_WORD)
		add_char_to_buffer(buffer, c);
	else if (c_type == C_OPERATOR)
	{
		// Operator: emit word first if buffer has content
		if (buffer->len > 0)
		{
			*consumed = 0;  // Don't consume operator, reprocess it
			return (T_WORD);
		}
		else
		{
			// Process operator
			add_char_to_buffer(buffer, c);
			if (c == '|')
				return (T_PIPE);
			else if (c == '<')
			{
				if (c_next == '<')
				{
					add_char_to_buffer(buffer, '<');
					*consumed = 2;	// Consume second '<'
					return (T_HEREDOC);
				}
				else
					return (T_REDIR_IN);
			}
			else if (c == '>')
			{
				if (c_next == '>')
				{
					add_char_to_buffer(buffer, '>');
					*consumed = 2;  // Consume second '>'
					return (T_APPEND);
				}
				else
					return (T_REDIR_OUT);
			}
		}
	}
	else if (c_type == C_SQUOTE)
	{
		if (buffer->len == 0)
			add_char_to_buffer(buffer, c);
		*state = STATE_IN_SQUOTE;
			
	}
	else if (c_type == C_DQUOTE)
	{
		if (buffer->len == 0)
			add_char_to_buffer(buffer, c);
		*state = STATE_IN_DQUOTE;
	}
	return (T_NONE);
}

int	state_quote(int *state, char c, int c_type, t_buffer *buffer)
{
    if (c_type == C_SQUOTE || c_type == C_DQUOTE)
    {
        if (buffer->len > 0 && (buffer->data[0] == '\'' || buffer->data[0] == '\"'))
            add_char_to_buffer(buffer, c);
        *state = STATE_NORMAL;
    }
    else
        add_char_to_buffer(buffer, c);
    return (T_NONE);
}
