/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:58:47 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/06 17:59:21 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	append_str(char *dst, char *src, int dst_index)
{
	int	i;

	if (!src || !src[0])
		return (0);
	i = 0;
	while (src[i])
		dst[dst_index++] = src[i++];
	return (i);
}

// echo $HOME $? $ $alas '$HOME $' "$h"
// caralho > "$HOME/out.txt"
char	*expand(t_env *env_list, int exit_status, char *str, int size)
{
	char		*out;
	t_str_state state;
	int         i;
	int			j;
	char    	*value;
	char		*key;
	int			key_size;

	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	state = STATE_NORMAL;
	i = 0;
	j = 0;
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
			value = get_value(env_list, exit_status, key);
			j += append_str(out, value, j);
			free(key);
			free(value);
		}
		else
			out[j++] = str[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}
