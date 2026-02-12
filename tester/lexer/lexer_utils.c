/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/15 15:22:05 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static int	compare_token(t_token expected, t_token actual, int index)
{
	if (expected.type != actual.type)
	{
		printf("Token %d type mismatch: expected %d, got %d\n",
			index, expected.type, actual.type);
		return (0);
	}
	if (!expected.value || !actual.value)
	{
		printf("Token %d value is NULL\n", index);
		return (0);
	}
	if (strcmp(expected.value, actual.value) != 0)
	{
		printf("Token %d value mismatch: expected '%s', got '%s'\n",
			index, expected.value, actual.value);
		return (0);
	}
	return (1);
}

static int	compare_lst(int token_count, t_token *head_actual, t_token *head_expected)
{
	t_token	*current_actual;
	t_token	*current_expected;
	
	// Compare
	current_actual = head_actual;
	current_expected = head_expected;
	int success = 1;
	int i = 0;
	while (current_actual && current_expected)
	{
		if (!compare_token(*current_expected, *current_actual, i))
			success = 0;
		current_actual = current_actual->next;
		current_expected = current_expected->next;
		i++;
	}
	
	// Check if both lists have the same length
	if (current_actual || current_expected)
	{
		printf("Token count mismatch: expected %d, got %d\n", token_count, i);
		success = 0;
	}
	
	free_tokens(head_actual);
	free_tokens(head_expected);
	return (success);
}

static t_token	*build_expected_tokens(t_token_type types[], char *values[], int count)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < count)
	{
		token = create_token(types[i], ft_strdup(values[i]));
		add_token_to_list(&head, &tail, token);
		i++;
	}
	return (head);
}

int	run_lexer_test(int test_num, char *name, char *input, 
	t_token_type types[], char *values[], int token_count)
{
	t_token	*head_actual;
	t_token	*head_expected;

	print_test_info(test_num, name, input);

	// Actual
	head_actual = lexer(input);

	// Expected
	if (token_count == 0)
		head_expected = NULL;
	else
		head_expected = build_expected_tokens(types, values, token_count);

	return (compare_lst(token_count, head_actual, head_expected));
}
