/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:34:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static char	**arraydup(char **input)
{
	char	**array;
	int		size;
	int		i;

	size = 0;
	while (input[size])
		size++;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		array[i] = strdup(input[i]);
		i++;
	}
	array[size] = NULL;
	return (array);
}

static t_redir	*redirdup(t_redir *input)
{
	t_redir		*redirs;
	int			size;
	int			i;

	size = 0;
	while (input[size].type != 0)
		size++;
	redirs = malloc(sizeof(t_redir) * (size + 1));
	if (!redirs)
		return (NULL);
	i = 0;
	while (i < size)
	{
		redirs[i].type = input[i].type;
		if (input[i].filename)
			redirs[i].filename = strdup(input[i].filename);
		else
			redirs[i].filename = NULL;
		redirs[i].quoted = input[i].quoted;
		i++;
	}
	redirs[size] = (t_redir){T_NONE, NULL, false};
	return (redirs);
}

static t_list	*build_actual_cmds(char *input)
{
	t_list		*cmd_list;
	t_token		*tokens;

	tokens = lexer(input);
	cmd_list = parser(tokens);
	free_tokens(&tokens);
	return (cmd_list);
}

void	build_expected_cmds(t_list **cmd_list, char **argv, t_redir *redirs)
{
	t_list		*cmd_node;
	t_cmd		*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->argv = arraydup(argv);
	cmd->redirs = redirdup(redirs);
	cmd_node = ft_lstnew(cmd);
	ft_lstadd_back(cmd_list, cmd_node);
}

int	run_parser_test(t_test_info info, t_list *head_expected)
{
	t_list	*head_actual;
	int		result;

	print_test_info(info);
	head_actual = build_actual_cmds(info.input);
	result = compare_cmd_list(head_actual, head_expected);
	ft_lstclear(&head_actual, del_cmd);
	ft_lstclear(&head_expected, del_cmd);
	return (result);
}
