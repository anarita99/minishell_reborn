/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:59:30 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/11 15:07:13 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	update_quote_state(t_str_state *state, char c)
{
	if (*state == STATE_NORMAL && c == '\'')
		return (*state = STATE_IN_SQUOTE, 1);
	if (*state == STATE_NORMAL && c == '\"')
		return (*state = STATE_IN_DQUOTE, 1);
	if (*state == STATE_IN_SQUOTE && c == '\'')
		return (*state = STATE_NORMAL, 1);
	if (*state == STATE_IN_DQUOTE && c == '\"')
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

bool	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	remove_from_array(char **array, int index)
{
	int	i;

	if (!array[index])
		return ;
	free(array[index]);
	i = index;
	while (array[i])
	{
		array[i] = array[i + 1];
		i++;
	}
}
