/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/07 17:49:40 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// also change int to bool
t_list	*lexer(char *input)
{
	t_list	*token_list;
	t_list	*current_node;

	int		i;
	int		state;
	char	c;
	t_token	*new_token;
	int		token_type;
	char	*token_value;
	t_sbuf		*buf;
	
	int		consumed;

	if (!input || !input[0])
		return (NULL);

	token_list = NULL;
	buf = sbuf_init(1);
	state = STATE_NORMAL;
	i = 0;
	while (input[i])
	{
		c = input[i];

		consumed = 1;  // By default, we consume the character
		token_type = T_NONE;

		// State machine
		if (state == STATE_NORMAL)
			token_type = state_normal(&state, c, buf, &consumed, input[i + 1]);
		else if (state == STATE_IN_SQUOTE)
			token_type = state_quote(&state, c, buf);
		else if (state == STATE_IN_DQUOTE)
			token_type = state_quote(&state, c, buf);

		// Create token if ready
		if (token_type != T_NONE)
		{
			token_value = ft_strdup(buf->data);
			new_token = create_token(token_type, token_value);
			if (new_token)
			{
				current_node = ft_lstnew(new_token);
				ft_lstadd_back(&token_list, current_node);
			}
			sbuf_reset(buf);
		}

		// Advance only if character was consumed
		if (consumed)
			i += consumed;
	}
	
	// Emit remaining buffer content as word
	if (buf->len > 0)
	{
		token_value = ft_strdup(buf->data);
		new_token = create_token(T_WORD, token_value);
		if (new_token)
		{
			current_node = ft_lstnew(new_token);
			ft_lstadd_back(&token_list, current_node);
		}
	}

	sbuf_free(buf);
	return (token_list);
}

// Examples of inputs:
// 	"hello"
// 	"ls | grep test | wc -l"
//	"cat < 'input.txt' > output.txt"
// t_token	*lexer(char *input)
// {
// 	int		i;
// 	int		state;
// 	char	c;
// 	t_token	*head;
// 	t_token	*tail;
// 	t_token	*new_token;
// 	int		token_type;
// 	char	*token_value;
// 	t_sbuf		*buf;
	
// 	int		consumed;

// 	if (!input || !input[0])
// 		return (NULL);

// 	head = NULL;
// 	tail = NULL;
// 	buf = sbuf_init(1);
// 	state = STATE_NORMAL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		c = input[i];

// 		consumed = 1;  // By default, we consume the character
// 		token_type = T_NONE;

// 		// State machine
// 		if (state == STATE_NORMAL)
// 			token_type = state_normal(&state, c, buf, &consumed, input[i + 1]);
// 		else if (state == STATE_IN_SQUOTE)
// 			token_type = state_quote(&state, c, buf);
// 		else if (state == STATE_IN_DQUOTE)
// 			token_type = state_quote(&state, c, buf);

// 		// Create token if ready
// 		if (token_type != T_NONE)
// 		{
// 			token_value = ft_strdup(buf->data);
// 			new_token = create_token(token_type, token_value);
// 			if (new_token)
// 				add_token_to_list(&head, &tail, new_token);
// 			sbuf_reset(buf);
// 		}

// 		// Advance only if character was consumed
// 		if (consumed)
// 			i += consumed;
// 	}
	
// 	// Emit remaining buffer content as word
// 	if (buf->len > 0)
// 	{
// 		token_value = ft_strdup(buf->data);
// 		new_token = create_token(T_WORD, token_value);
// 		if (new_token)
// 			add_token_to_list(&head, &tail, new_token);
// 	}

// 	sbuf_free(buf);
// 	return (head);
// }
