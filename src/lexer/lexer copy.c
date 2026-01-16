/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 15:55:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Examples of inputs:
// 	"hello"
// 	"ls | grep test | wc -l"
//	"cat < 'input.txt' > output.txt"
t_token	*lexer(char *input)
{
	int		i;
	int		state;
	char	c;
	int		c_type;

	t_token	*head;
	t_token	*tail;
	t_token	*new_token;
	int		new_token_type;
	char	*new_token_value;

	int 	in_word;
	int		start_idx;
	int		end_idx;

	t_buffer	*buffer;

	if (!input || !input[0])
		return (NULL);

	// create buffer
	buffer = create_buffer(input);
	
	state = STATE_NORMAL;
	in_word = 0;
	i = 0;
	while (input[i])
	{
		c = input[i];
		
	// Character classification (space, alnum, quote, operator, etc.)
		c_type = ?;

	// State transitions
		
		if (state = STATE_NORMAL)
		{
			// If c is a word, add it to a buffer
			if (c_type == T_ALNUM)
			{
				add_char_to_buffer(buffer, c);
			}

			// Change state if c is a quote
			if (c_type = T_QUOTE)
			{
				if (c == '\'')
					state = STATE_IN_SQUOTE;
				else
					state = STATE_IN_DQUOTE;
				start_idx = i + 1;
				i++;
				continue ;
			}
		}

		if (c == '\'' || c == '\"')
		{
			if (state == STATE_NORMAL)
			{
				if (c == '\'')
					state = STATE_IN_SQUOTE;
				else
					state = STATE_IN_DQUOTE;
				start_idx = i + 1;
				i++;
				continue ;
			}
			else
			{
				; // TODO
			}
		}

		if (c == ' ')
		{
			i++;
			continue;
		}

	// Token creation (value has to be malloc before creating)
		new_token = create_token(new_token_type, new_token_value);

	// List management (maybe no need for if)
		if (new_token)
		{
			add_token_to_list(&head, &tail, new_token);
			new_token = NULL;
		}

	}
}
