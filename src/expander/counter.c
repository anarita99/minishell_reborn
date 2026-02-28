/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:57:51 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 18:49:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	get_env_value_size(t_env *env_list, char *str, int *i)
{
	int		size;
	char	*varkey;
	char	*varvalue;

	size = 0;
	varkey = get_env_key(str, i);
	if (varkey)
	{
		varvalue = get_env_value(env_list, varkey);
		free(varkey);
		if (varvalue)
			size += ft_strlen(varvalue);
	}
	return (size);
}

int counter(t_env *env_list, char *str)
{
	int         count;
	t_str_state state;
	int         i;
	char        c;

	state = STATE_NORMAL;
	count = 0;
	i = 0;
	while (str[i])
	{
		c = str[i];
		if (state == STATE_IN_SQUOTE && c == '\'')
			state = STATE_NORMAL;
		else if (state == STATE_NORMAL && c == '\'')
			state = STATE_IN_SQUOTE;
		else if (state == STATE_NORMAL && c == '\"')
			state = STATE_IN_DQUOTE;
		else if (state == STATE_IN_DQUOTE && c == '\"')
			state = STATE_NORMAL;
		else if (c == '$')
			get_env_value_size(env_list, str, &i);
		else
			count++;
		i++;
	}
	count++;
	return (count);
}
