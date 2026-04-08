/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 16:26:31 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_argc(t_list *current_node)
{
	int		argc;
	t_token	*current_token;

	argc = 0;
	while (current_node)
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == T_PIPE)
			break ;
		if (is_token_operator(current_token))
		{
			current_node = current_node->next;
			if (!current_node)
				break ;
		}
		else
			argc++;
		current_node = current_node->next;
	}
	return (argc);
}

char	**get_argv(t_list *current_node)
{
	char	**argv;
	t_token	*current_token;
	int		argc;
	int		i;

	argc = get_argc(current_node);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		current_token = (t_token *)current_node->content;
		if (is_token_operator(current_token))
			current_node = current_node->next;
		else
		{
			argv[i] = ft_strdup(current_token->value);
			i++;
		}
		current_node = current_node->next;
	}
	argv[i] = NULL;
	return (argv);
}
