/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:15 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/31 11:39:25 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	**expand_argv(char **old_argv, t_env *env_list, int exit_status)
{
	char	**new_argv;
	t_list	*words;
	int		i;

	words = NULL;
	i = 0;
	while (old_argv[i])
	{
		expand_str(&words, old_argv[i], env_list, exit_status, false);
		i++;
	}
	new_argv = convert_lst_to_argv(words);
	ft_lstclear(&words, free);
	return (new_argv);
}

char	*expand_filename(char *input, t_env *env_list, int exit_status, bool is_heredoc)
{
	t_list	*words;
	char	*output;

	words = NULL;
	expand_str(&words, input, env_list, exit_status, is_heredoc);
	output = convert_lst_to_str(words);
	ft_lstclear(&words, free);
	return (output);
}

void	expander(t_list **commands, t_env *env_list, int exit_status)
{
	t_list  *current_node;
	t_cmd   *current_cmd;
	char	**old_argv;
	char	*old_filename;
	int		i;
	
	current_node = *commands;
	while (current_node)
	{
		current_cmd = (t_cmd *)current_node->content;
		old_argv = current_cmd->argv;
		current_cmd->argv = expand_argv(old_argv, env_list, exit_status);
		ft_freearray(old_argv);

		// Redirs part
		i = 0;
		while (current_cmd->redirs && current_cmd->redirs[i].filename != NULL && current_cmd->redirs[i].type != T_HEREDOC)
		{
			old_filename = current_cmd->redirs[i].filename;
			current_cmd->redirs[i].filename = expand_filename(old_filename, env_list, exit_status, false);
			free(old_filename);
			i++;
		}

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
