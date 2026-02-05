/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/04 00:00:00 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		get_argc(t_token *current_token)
{
	int	argc;

	argc = 0;
	while (current_token && current_token->type == T_WORD)
	{
		argc++;
		current_token = current_token->next;
	}
	return (argc);
}

static char	**get_argv(t_token **current_token, int argc)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup((*current_token)->value);
		*current_token = (*current_token)->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

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

static t_redir	*get_redirs(t_token **current_token)
{
	t_redir	*redirs;
	int		redir_count;
	int		i;

	redir_count = get_redir_count(*current_token);
	redirs = malloc(sizeof(t_redir) * (redir_count + 1));
	if (!redirs)
		return (NULL);
	i = 0;
	while (i < redir_count)
	{
		if (is_token_operator(*current_token))
		{
			redirs[i].type = (*current_token)->type;
			redirs[i].filename = ft_strdup((*current_token)->next->value);
			redirs[i].quoted = false;	// TODO
			i++;
		}
		*current_token = (*current_token)->next->next;
	}
	redirs[i].type = T_NONE;
	redirs[i].filename = NULL;
	return (redirs);
}

t_cmd	*get_next_cmd(t_token **current_token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	argc = get_argc(*current_token);
	cmd->argv = get_argv(current_token, argc);
	cmd->redirs = get_redirs(current_token);
	return (cmd);
}

void	del_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)cmd_ptr;
	if (!cmd)
		return ;
	
	// Free argv array
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	
	// Free redirs array
	if (cmd->redirs)
	{
		i = 0;
		while (cmd->redirs[i].type != T_NONE)
		{
			if (cmd->redirs[i].filename)
				free(cmd->redirs[i].filename);
			i++;
		}
		free(cmd->redirs);
	}
	
	// Free the cmd itself
	free(cmd);
}
