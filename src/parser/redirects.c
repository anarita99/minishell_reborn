/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/08 16:25:58 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_redir_count(t_list *current_node)
{
	int		count;
	t_token	*current_token;

	count = 0;
	while (current_node)
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == T_PIPE)
			break ;
		if (is_token_operator(current_token))
			count++;
		current_node = current_node->next;
	}
	return (count);
}

static bool	is_str_quoted(const char *str)
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

static t_redir	create_redir(t_token_type type, const char *filename)
{
	t_redir	redir;

	if (type == T_NONE || !filename)
	{
		redir.type = T_NONE;
		redir.filename = NULL;
		redir.quoted = false;
	}
	else
	{
		redir.type = type;
		redir.filename = ft_strdup(filename);
		redir.quoted = is_str_quoted(filename);
	}
	return (redir);
}

t_redir	*get_redirs(t_list *current_node)
{
	t_token	*current_token;
	t_token	*file_token;
	t_redir	*redirs;
	int		redir_count;
	int		i;

	redir_count = get_redir_count(current_node);
	redirs = malloc(sizeof(t_redir) * (redir_count + 1));
	if (!redirs)
		return (NULL);
	i = 0;
	while (i < redir_count)
	{
		current_token = (t_token *)current_node->content;
		if (is_token_operator(current_token))
		{
			file_token = (t_token *)(current_node->next)->content;
			redirs[i] = create_redir(current_token->type, file_token->value);
			i++;
		}
		current_node = current_node->next;
	}
	redirs[i] = create_redir(T_NONE, NULL);
	return (redirs);
}
