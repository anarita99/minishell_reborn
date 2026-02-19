/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:27:03 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 14:43:25 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_to_list(t_token **head, t_token **tail, t_token *token)
{
	if (!token)
		return ;

	if (!*head)
	{
		*head = token;
		*tail = token;
		return ;
	}
	(*tail)->next = token;
	token->prev = *tail;
	*tail = token;
}

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

int	is_token_operator(t_token *token)
{
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT ||
			token->type == T_HEREDOC || token->type == T_APPEND);
}

int	validate_tokens(t_token *head)
{
	int	i;
	t_token *current;

	current = head;
	i = 0;
	while (current)
	{
		// Error: Can't start or end with PIPE
		if ((i == 0 || !current->next) && current->type == T_PIPE)
		{
			print_syntax_error(current->value);
			return (0);
		}

		// Error: Token after OPERATOR needs to be WORD
		if (is_token_operator(current))
		{
			if (!current->next)
			{
				print_syntax_error(NULL);
				return (0);
			}
			else if (current->next->type != T_WORD)
			{
				print_syntax_error(current->next->value);
				return (0);
			}
		}

		// Error: Token after PIPE needs to not be PIPE
		if (current->type == T_PIPE && current->next && current->next->type == T_PIPE)
		{
			print_syntax_error(current->value);
			return (0);
		}
		current = current->next;
		i++;
	}
	return (1);
}
