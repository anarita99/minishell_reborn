/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:15 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/09 23:18:34 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_argv(char ***argv)
{
	char	**old_argv;
	t_list	*words;
	t_list	*tmp;
	int		i;

	if (!argv || !*argv)
		return ;
	old_argv = *argv;
	words = NULL;
	i = 0;
	while ((*argv)[i])
	{
		tmp = expand_input((*argv)[i], EXPAND_ARGV);
		ft_lstadd_back(&words, tmp);
		i++;
	}
	*argv = convert_lst_to_argv(words);
	ft_lstclear(&words, free);
	ft_freearray(old_argv);
}

static void	expand_redirs(t_redir *redirs)
{
	int		i;
	char	*old_filename;
	t_list	*words;

	if (!redirs)
		return ;
	i = 0;
	while (redirs[i].filename != NULL)
	{
		old_filename = redirs[i].filename;
		words = expand_input(old_filename, EXPAND_REDIR);
		redirs[i].filename = convert_lst_to_str(words);
		ft_lstclear(&words, free);
		free(old_filename);
		i++;
	}
}

void	expander(t_list **commands)
{
	t_list	*current_node;
	t_cmd	*current_cmd;

	current_node = *commands;
	while (current_node)
	{
		current_cmd = (t_cmd *)current_node->content;
		expand_argv(&current_cmd->argv);
		expand_redirs(current_cmd->redirs);
		current_node = current_node->next;
	}
}
