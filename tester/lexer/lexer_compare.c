/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:14:14 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/10 23:14:14 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static int	compare_token(t_token *actual, t_token *expected, int index)
{
	if (actual->type != expected->type)
	{
		printf("Token %d type mismatch: expected %d, got %d\n",
			index, expected->type, actual->type);
		return (0);
	}
	if (!actual->value || !expected->value)
	{
		printf("Token %d value is NULL\n", index);
		return (0);
	}
	if (strcmp(actual->value, expected->value) != 0)
	{
		printf("Token %d value mismatch: expected '%s', got '%s'\n",
			index, expected->value, actual->value);
		return (0);
	}
	return (1);
}

int	compare_tokens(t_token *actual, t_token *expected, int count)
{
	int	success;
	int	i;

	success = 1;
	i = 0;
	while (actual && expected)
	{
		if (!compare_token(actual, expected, i))
			success = 0;
		actual = actual->next;
		expected = expected->next;
		i++;
	}
	if (actual || expected)
	{
		printf("Token count mismatch: expected %d, got %d\n", count, i);
		success = 0;
	}
	return (success);
}
