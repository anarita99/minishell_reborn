/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:14:11 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/10 23:14:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static t_token	*build_actual_tokens(char *input)
{
	return (lexer(input));
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

int	run_lexer_test(t_test_info info, t_token_type types[], char *values[], int count)
{
	t_token	*head_actual;
	t_token	*head_expected;
	int		result;

	print_test_info(info);
	head_actual = build_actual_tokens(info.input);
	head_expected = build_expected_tokens(types, values, count);
	result = compare_tokens(head_actual, head_expected, count);
	free_tokens(&head_actual);
	free_tokens(&head_expected);
	return (result);
}
