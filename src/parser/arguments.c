/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/04 15:41:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_argc(t_token *current_token)
{
	int	argc;

	argc = 0;
	while (current_token && current_token->type != T_PIPE)
	{
		if (is_token_operator(current_token))
			current_token = current_token->next;
		else
			argc++;
		current_token = current_token->next;
	}
	return (argc);
}

char	**get_argv(t_token *current_token)
{
	char	**argv;
	int		argc;
	int		i;

	argc = get_argc(current_token);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		if (is_token_operator(current_token))
			current_token = current_token->next;
		else
		{
			argv[i] = ft_strdup(current_token->value);
			i++;
		}
		current_token = current_token->next;
	}
	argv[i] = NULL;
	return (argv);
}
