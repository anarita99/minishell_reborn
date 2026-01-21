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
	int		token_type;
	char	*token_value;
	t_buffer	*buffer;
	int		consumed;

	if (!input || !input[0])
		return (NULL);

	head = NULL;
	tail = NULL;
	buffer = create_buffer(input);
	state = STATE_NORMAL;
	i = 0;
	
	while (input[i])
	{
		c = input[i];
		c_type = get_c_type(c);
		
		if (c_type == -1)
		{
			i++;
			continue;
		}

		consumed = 1;  // By default, we consume the character
		token_type = T_NONE;

		// State machine
		if (state == STATE_NORMAL)
			token_type = state_normal(&state, c, c_type, buffer, &consumed, input, &i);
		else if (state == STATE_IN_SQUOTE)
			token_type = state_squote(&state, c, c_type, buffer);
		else if (state == STATE_IN_DQUOTE)
			token_type = state_dquote(&state, c, c_type, buffer);

		// Create token if ready
		if (token_type != T_NONE)
		{
			token_value = ft_strdup(buffer->data);
			new_token = create_token(token_type, token_value);
			if (new_token)
				add_token_to_list(&head, &tail, new_token);
			reset_buffer(buffer);
		}

		// Advance only if character was consumed
		if (consumed)
			i++;
	}
	
	// Emit remaining buffer content as word
	if (buffer->len > 0)
	{
		token_value = ft_strdup(buffer->data);
		new_token = create_token(T_WORD, token_value);
		if (new_token)
			add_token_to_list(&head, &tail, new_token);
	}

	free(buffer->data);
	free(buffer);
	return (head);
}
