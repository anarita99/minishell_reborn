/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:15 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/04 15:23:22 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_argv(char ***argv, t_env *env_list, int status)
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
		tmp = expand_input((*argv)[i], env_list, status, EXPAND_ARGV);
		ft_lstadd_back(&words, tmp);
		i++;
	}
	*argv = convert_lst_to_argv(words);
	ft_lstclear(&words, free);
	ft_freearray(old_argv);
}

static void	expand_redirs(t_redir *redirs, t_env *env_list, int status)
{
	int		i;
	char	*old_filename;
	t_list	*words;

	if (!redirs)
		return ;
	i = 0;
	while (redirs[i].filename != NULL)
	{
		if (redirs[i].type != T_HEREDOC)
		{
			old_filename = redirs[i].filename;
			words = expand_input(old_filename, env_list, status, EXPAND_REDIR);
			redirs[i].filename = convert_lst_to_str(words);
			ft_lstclear(&words, free);
			free(old_filename);
		}
		i++;
	}
}

void	expander(t_list **commands, t_env *env_list, int status)
{
	t_list	*current_node;
	t_cmd	*current_cmd;

	current_node = *commands;
	while (current_node)
	{
		current_cmd = (t_cmd *)current_node->content;
		expand_argv(&current_cmd->argv, env_list, status);
		expand_redirs(current_cmd->redirs, env_list, status);
		current_node = current_node->next;
	}
}

// [$ola]				= [ls, -l]
// ["$ola"]				= [ls -l]
// ['$ola']				= [$ola]

// [$ola, crazy]		= [ls, -l, crazy]
// ["$ola crazy"]		= [ls -l, crazy]
// ['$ola crazy']		= [$ola, crazy]

// [pre$ola]			= [prels, -l]
// ["pre$ola"]			= [prels -l]
// [$ola$ola]			= [ls, -lls, -l]

// [pre$ola"pos"] = [prels, -lpos]

// [ls, $empty, -la]	= [ls, -la]
// [ls, "$empty", -la]	= [ls, , -la]

// [alas'ignore $var'"damn $ola"post] = [alasignore $vardamn ls -lpost]

// echo                 = echo
// 'alas"da"mn$ec"'     = alas"da"mn$ec"
// "alas$wow"           = alaswow
// alas$ crazy          = alas crazy
// abc$a$ '$c"razy'		= abcabc $c"razy
// 'hello "w"orld'		= hello "w"orld
