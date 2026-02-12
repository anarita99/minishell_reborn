/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:34:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static int	compare_argv(char **actual, char **expected)
{
	int	i;

	if (!expected && !actual)
		return (1);
	if (!expected || !actual)
		return (0);
	
	i = 0;
	while (actual[i] && expected[i])
	{
		if (strcmp(expected[i], actual[i]) != 0)
			return (0);
		i++;
	}
	if (actual[i] != expected[i])
		return (0);
	return (1);
}

static int	compare_redirects(t_redir *actual, t_redir *expected)
{
	int	i;

	if (!expected && !actual)
		return (1);
	if (!expected || !actual)
		return (0);
	
	i = 0;
	while (actual[i].type != T_NONE && expected[i].type != T_NONE)
	{
		if (expected[i].type != actual[i].type)
			return (0);
		if (expected[i].filename && actual[i].filename)
		{
			if (strcmp(expected[i].filename, actual[i].filename) != 0)
				return (0);
		}
		else if (expected[i].filename != actual[i].filename)
			return (0);
		if (expected[i].quoted != actual[i].quoted)
			return (0);
		i++;
	}
	if (expected[i].type != actual[i].type)
		return (0);
	return (1);
}

int	compare_cmd_list(t_list *actual, t_list *expected)
{
	t_cmd	*actual_cmd;
	t_cmd	*expected_cmd;
	int		success;

	success = 1;
	while (actual && expected)
	{
		actual_cmd = (t_cmd *)actual->content;
		expected_cmd = (t_cmd *)expected->content;
		if (!compare_argv(actual_cmd->argv, expected_cmd->argv))
			success = 0;
		if (!compare_redirects(actual_cmd->redirs, expected_cmd->redirs))
			success = 0;
		actual = actual->next;
		expected = expected->next;
	}
	if (actual || expected)
	{
		printf("Command count mismatch\n");
		success = 0;
	}
	return (success);
}
