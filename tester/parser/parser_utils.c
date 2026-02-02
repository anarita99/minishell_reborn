/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:34:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"
#include "../../includes/parser.h"

static int	compare_argv(char **expected, char **actual, int argc)
{
	int	i;

	if (!expected && !actual)
		return (1);
	if (!expected || !actual)
		return (0);
	
	i = 0;
	while (i < argc)
	{
		if (!expected[i] && !actual[i])
			break;
		if (!expected[i] || !actual[i])
			return (0);
		if (strcmp(expected[i], actual[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	run_parser_test(int test_num, char *name, char *input, char *expected_argv[], int argc)
{
	t_token	*tokens;
	t_list	*cmd_list;
	t_cmd	*cmd;
	int		success;

	print_test_info(test_num, name, input);

	// Parse input
	tokens = lexer(input);
	cmd_list = parser(tokens);
	free_tokens(tokens);

	// Check result
	success = 1;
	if (!cmd_list || !cmd_list->content)
		success = 0;
	else
	{
		cmd = (t_cmd *)cmd_list->content;
		if (!compare_argv(expected_argv, cmd->argv, argc))
			success = 0;
	}
	
	return (success);
}
