/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/09 21:58:03 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_lexer_ctx(t_list **token_list, t_sbuf **buf, int *state, int *i)
{
	*token_list = NULL;
	*buf = sbuf_init(1);
	*state = STATE_NORMAL;
	*i = 0;
}

t_list	*lexer(const char *input)
{
	t_list	*token_list;
	int		i;
	int		state;
	int		token_type;
	t_sbuf	*buf;

	if (!input || !input[0])
		return (NULL);
	init_lexer_ctx(&token_list, &buf, &state, &i);
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
	if (!validate_tokens(token_list))
	{
		ft_lstclear(&token_list, del_token);
		return (NULL);
	}
	return (token_list);
}
