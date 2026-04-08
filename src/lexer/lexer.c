/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 19:58:01 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*lexer(const char *input)
{
	t_list	*token_list;
	int		i;
	int		state;
	int		token_type;
	t_sbuf	*buf;

	if (!input || !input[0])
		return (NULL);
	token_list = NULL;
	buf = sbuf_init(1);
	state = STATE_NORMAL;
	i = 0;
	while (input[i])
	{
		token_type = state_machine(&state, buf, input[i], input[i + 1]);
		if (token_type != T_NONE)
			append_token_to_lst(&token_list, token_type, buf);
		i += calc_consumed_chars(token_type);
	}
	if (buf->len > 0)
		append_token_to_lst(&token_list, T_WORD, buf);
	sbuf_free(buf);
	return (token_list);
}
