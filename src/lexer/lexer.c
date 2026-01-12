/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 14:03:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

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
		// Skip spaces
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}

		token_type = find_token_type(input, i);
		// printf("Token type = %i\n", token_type);
	
		// Handle operators
		tmp = NULL;
		if (token_type == T_PIPE)
		{
			tmp = create_operator(T_PIPE, "|");
			i++;
		}
		else if (token_type == T_REDIR_IN)
		{
			tmp = create_operator(T_REDIR_IN, "<");
			i++;
		}
		else if (token_type == T_REDIT_OUT)
		{
			tmp = create_operator(T_REDIT_OUT, ">");
			i++;
		}
		else if (token_type == T_HEREDOC)
		{
			tmp = create_operator(T_HEREDOC, "<<");
			i += 2;
		}
		else if (token_type == T_APPEND)
		{
			tmp = create_operator(T_APPEND, ">>");
			i += 2;
		}

		// Handle words
		else if (token_type == T_WORD)
		{
			if (found_word == 0)
			{
				found_word = 1;
				start_idx = i;
			}
			// Check if word continues
			if (find_token_type(input, i + 1) != T_WORD)
			{
				end_idx = i;
				found_word = 0;
				tmp = create_word(input, start_idx, end_idx);
			}
			i++;
		}

		// Unknown token type
		else
		{
			i++;
			continue;
		}

		// Add token to the list if we created one
		if (tmp)
		{
			if (list_created == 0)
			{
				head = tmp;
				tail = tmp;
				list_created = 1;
			}
			else
				add_token_to_list(&head, &tail, tmp);
		}
	}
	return (head);
}
