/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:59:30 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/23 17:15:21 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	freearray(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**convert_lst_to_argv(t_list *lst)
{
	char	**argv;
	int		lst_size;
	t_list	*current_node;
	char	*current_word;
	int		i;

	lst_size = ft_lstsize(lst);
	argv = malloc(sizeof(char *) * (lst_size + 1));
	if (!argv)
		return (NULL);
	current_node = lst;
	i = 0;
	while (i < lst_size)
	{
		current_word = (char *)current_node->content;
		argv[i] = strdup(current_word);
		current_node = current_node->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	update_quote_state(t_str_state *state, char c)
{
	if (c != '\'' && c != '\"')
		return (0);
	if (*state == STATE_NORMAL)
	{
		if (c == '\'')
			*state = STATE_IN_SQUOTE;
		else
			*state = STATE_IN_DQUOTE;
		return (1);
	}
	if ((*state == STATE_IN_SQUOTE && c == '\'')
		|| (*state == STATE_IN_DQUOTE && c == '\"'))
		return (*state = STATE_NORMAL, 1);
	return (0);
}

int	get_key_size(char *str, int i)
{
	int		start;

	if (!str || !str[i] || str[i] != '$')
		return (0);
	i++;
	if (str[i] == '?')
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - start);
}

char *get_value(t_env *env_list, int exit_status, char *key)
{
	char	*env_value;

	if (!key || !key[0])
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(exit_status));
	env_value = get_env_value(env_list, key);
	if (!env_value)
		return (NULL);
	return (strdup(env_value));
}
