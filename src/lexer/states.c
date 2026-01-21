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

// alas>alas
// alas|alas
// |alas>>alas

// Returns token type when the token value is ready
// Returns T_NONE when the token value is not ready
// int	state_normal(int *state, char c, int c_type, t_buffer *buffer, char c_next)
// {
// 	// Delimiter: if buffer has content, emit word token
// 	if (c_type == C_DELIMITER)
// 	{
// 		if (buffer->len > 0)
// 			return (T_WORD);
// 		return (T_NONE);
// 	}

// 	// If c is a word character, add it to the buffer
// 	if (c_type == C_WORD)
// 	{
// 		add_char_to_buffer(buffer, c);
// 		return (T_NONE);
// 	}

// 	// Operators: if buffer has content, we need to emit word first
// 	// The operator will be handled on next iteration
// 	if (c_type == C_OPERATOR)
// 	{
// 		// If we have a word in buffer, emit it first
// 		if (buffer->len > 0)
// 			return (T_WORD);
		
// 		// Otherwise, process the operator
// 		if (c == '|')
// 		{
// 			add_char_to_buffer(buffer, c);
// 			return (T_PIPE);
// 		}

// 		if (c == '<')
// 		{
// 			add_char_to_buffer(buffer, c);
// 			if (c_next == c)
// 			{
// 				add_char_to_buffer(buffer, c_next);
// 				return (T_HEREDOC);
// 			}
// 			return (T_REDIR_IN);
// 		}

// 		if (c == '>')
// 		{
// 			add_char_to_buffer(buffer, c);
// 			if (c_next == c)
// 			{
// 				add_char_to_buffer(buffer, c_next);
// 				return (T_APPEND);
// 			}
// 			return (T_REDIT_OUT);
// 		}
// 	}

// 	// Quote: if buffer has content, emit word first before starting quote
// 	if (c_type == C_SQUOTE || c_type == C_DQUOTE)
// 	{
// 		if (buffer->len > 0)
// 			return (T_WORD);
		
// 		// Start quote state
// 		if (c_type == C_SQUOTE)
// 			*state = STATE_IN_SQUOTE;
// 		if (c_type == C_DQUOTE)
// 			*state = STATE_IN_DQUOTE;
// 	}

// 	return (T_NONE);
// }

int	state_normal(int *state, char c, int c_type, t_buffer *buffer, int *consumed, char c_next)
{
	if (c_type == C_DELIMITER)
	{
		// Delimiter: emit word if buffer has content
		if (buffer->len > 0)
			return (T_WORD);
	}
	else if (c_type == C_WORD)
	{
		// Regular word character: add to buffer
		add_char_to_buffer(buffer, c);
	}
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
					return (T_REDIT_OUT);
			}
		}
	}
	else if (c_type == C_SQUOTE)
	{
		// Start single quote: emit word first if buffer has content
		if (buffer->len > 0)
		{
			*consumed = 0;
			return (T_WORD);
		}
		else
			*state = STATE_IN_SQUOTE;
	}
	else if (c_type == C_DQUOTE)
	{
		// Start double quote: emit word first if buffer has content
		if (buffer->len > 0)
		{
			*consumed = 0;
			return (T_WORD);
		}
		else
			*state = STATE_IN_DQUOTE;
	}
	return (T_NONE);
}

// 'ala$|<s'
int state_squote(int *state, char c, int c_type, t_buffer *buffer)
{
	// Quote: Word ends here
	if (c_type == C_SQUOTE)
	{
		*state = STATE_NORMAL;
		return (T_WORD);
	}

	// Any other char: Adds to buffer
	else
	{
		add_char_to_buffer(buffer, c);
		return (T_NONE);
	}
}

int state_dquote(int *state, char c, int c_type, t_buffer *buffer)
{
	// Quote: Word ends here
	if (c_type == C_DQUOTE)
	{
		*state = STATE_NORMAL;
		return (T_WORD);
	}
	
	// $vars
	// TO IMPLEMENT

	// Any other char: Adds to buffer
	else
	{
		add_char_to_buffer(buffer, c);
		return (T_NONE);
	}
}
