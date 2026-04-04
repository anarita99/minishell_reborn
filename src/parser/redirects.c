/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/04 15:43:12 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_redir_count(t_token *current_token)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (current_token && current_token->type != T_PIPE)
	{
		if (is_token_operator(current_token))
			count++;
		current_token = current_token->next;
		i++;
	}
	return (count);
}

static bool	is_str_quoted(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static t_redir	create_redir(t_token *current_token)
{
	t_redir	redir;

	if (!current_token)
	{
		redir.type = T_NONE;
		redir.filename = NULL;
		redir.quoted = false;
	}
	else
	{
		redir.type = current_token->type;
		redir.filename = ft_strdup(current_token->next->value);
		redir.quoted = is_str_quoted(redir.filename);
	}
	return (redir);
}

t_redir	*get_redirs(t_token *current_token)
{
	t_redir	*redirs;
	int		redir_count;
	int		i;

	redir_count = get_redir_count(current_token);
	redirs = malloc(sizeof(t_redir) * (redir_count + 1));
	if (!redirs)
		return (NULL);
	i = 0;
	while (i < redir_count)
	{
		if (is_token_operator(current_token))
		{
			redirs[i] = create_redir(current_token);
			i++;
		}
		current_token = current_token->next;
	}
	redirs[i] = create_redir(NULL);
	return (redirs);
}
