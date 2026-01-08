/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:27:03 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/08 15:42:03 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	(*tail)->next = token;
	token->prev = *tail;
	*tail = token;
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	print_tokens(t_token *head)
{
	int	i;
	t_token *current;

	current = head;
	i = 0;
	while (current)
	{
		printf("Token %i:\n", i);
		printf("- Type: %i\n", current->type);
		printf("- Value: %s\n", current->value);
		i++;
		current = current->next;
	}
}
