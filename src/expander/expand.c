/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:58:47 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 18:58:58 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void append_var(t_env *env_list, char *str, int *i, char *expanded_str, int *j)
{
    char    *key;
    char    *value;
    int     k;

    key = get_env_key(str, i);
    if (!key)
        return ;
    value = get_env_value(env_list, key);
    printf("Env Var = [%s : %s]\n", key, value);
    free(key);
    k = 0;
    while (value && value[k])
    {
        expanded_str[*j] = value[k];
        (*j)++;
        k++;
    }
}

char	*expand(t_env *env_list, char *str, int size)
{
	t_str_state state;
	int         i;
	int			j;
	char        c;
	char		*expanded_str;

	expanded_str = malloc(sizeof(char) * (size + 1));
	state = STATE_NORMAL;
	i = 0;
	j = 0;
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
			append_var(env_list, str, &i, expanded_str, &j);
		else
			expanded_str[j++] = c;
		i++;
	}
	expanded_str[j] = '\0';
	return (expanded_str);
}


// old
// char	*expand(t_env *env_list, char *str, int size)
// {
// 	t_str_state state;
// 	int         i;
// 	int			j;
// 	char        c;
// 	char		*expanded_str;

// 	expanded_str = malloc(sizeof(char) * (size + 1));
// 	state = STATE_NORMAL;
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		c = str[i];
// 		if (state == STATE_NORMAL)
// 		{
// 			if (c == '\'')
// 				state = STATE_IN_SQUOTE;
// 			else if (c == '\"')
// 				state = STATE_IN_DQUOTE;
// 			else if (c == '$')
// 				append_var(env_list, str, &i, expanded_str, &j);
// 			else
// 			{
// 				expanded_str[j] = c;
// 				j++;
// 			}
				
// 		}
// 		else if (state == STATE_IN_SQUOTE)
// 		{
// 			if (c == '\'')
// 				state = STATE_NORMAL;
// 			else
// 			{
// 				expanded_str[j] = c;
// 				j++;
// 			}
// 		}
// 		else if (state == STATE_IN_DQUOTE)
// 		{
// 			if (c == '\"')
// 				state = STATE_NORMAL;
// 			else if (c == '$')
// 				append_var(env_list, str, &i, expanded_str, &j);
// 			else
// 			{
// 				expanded_str[j] = c;
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	expanded_str[j] = '\0';
// 	return (expanded_str);
// }
