/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:57:51 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/06 17:56:38 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	get_value_size(t_env *env_list, int exit_status, char *key)
{
	int		size;
	char	*value;

	if (!key || !key[0])
		return (0);
	value = get_value(env_list, exit_status, key);
	if (!value || !value[0])
		return (0);
	size = ft_strlen(value);
	free(value);
	return (size);
}

int counter(t_env *env_list, int exit_status, char *str)
{
	int         count;
	t_str_state state;
	int         i;
	char		*key;
	int			key_size;

	state = STATE_NORMAL;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (update_quote_state(&state, str[i]))
		{
			i++;
			continue ;
		}
		if (str[i] == '$' && state != STATE_IN_SQUOTE
			&& str[i + 1] && str[i + 1] != ' ')
		{
			key_size = get_key_size(str, i);
			key = ft_substr(str, i + 1, key_size);
			i += key_size;
			count += get_value_size(env_list, exit_status, key);
			free(key);
		}
		else
			count++;
		i++;
	}
	return (count);
}
