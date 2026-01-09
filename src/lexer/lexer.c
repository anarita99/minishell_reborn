/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/09 15:10:20 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*lexer(char *input)
{
	int		i;
	int		found_word;
	int		start_idx;
	int		end_idx;
	t_token	*head;
	t_token	*tail;
	t_token	*tmp;
	int		list_created;
	int		token_type;

	if (!input || !input[0])
		return (NULL);
	found_word = 0;
	list_created = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;

		token_type = find_token_type(input, i);
		// printf("Token type = %i\n", token_type);
	
		
		if (token_type == T_PIPE)
			tmp = create_operator(T_PIPE, "|");
		if (token_type == T_REDIR_IN)
			tmp = create_operator(T_REDIR_IN, "<");
		if (token_type == T_REDIT_OUT)
			tmp = create_operator(T_REDIT_OUT, ">");
		if (token_type == T_HEREDOC)
			tmp = create_operator(T_HEREDOC, "<<");
		if (token_type == T_APPEND)
			tmp = create_operator(T_APPEND, ">>");
		
		
		if (token_type == T_WORD && found_word == 0)
		{
			found_word = 1;
			start_idx = i;
		}
		if (found_word && find_token_type(input, i + 1) != T_WORD)
		{
			end_idx = i;
			found_word = 0;
			tmp = create_word(input, start_idx, end_idx);
		}


		if (list_created == 0)
		{
			head = tmp;
			tail = tmp;
			list_created = 1;
		}
		else
			add_token_to_list(&head, &tail, tmp);

		i++;
	}
	return (head);
}
