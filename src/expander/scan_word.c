/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:01:32 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/26 13:38:44 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// words_head = NULL
// buf = pre
// value = ls -l
// result = prels, -l
static void	handle_unquoted_expansion(t_list **words_head, t_sbuf *buf, char *value)
{
	char	**value_split;
	int		i;
	char	*tmp;

	value_split = ft_split(value, ' ');
	if (!value_split)
		return ;
	sbuf_push_str(buf, value_split[0]);
	if (value_split[1] != NULL)
	{
		ft_lstadd_back(words_head, ft_lstnew(strdup(buf->data)));
		sbuf_reset(buf);
	}
	i = 1;
	while (value_split[i])
	{
		if (!value_split[i + 1])
			sbuf_push_str(buf, value_split[i]);
		else
		{
			tmp = strdup(value_split[i]);
			ft_lstadd_back(words_head, ft_lstnew(tmp));
		}
		i++;
	}
	ft_freearray(value_split);
}

void expand_str(t_list **expanded_words, char *input, t_env *env_list, int exit_status)
{
	t_sbuf		*buf;
	int			i;
	t_str_state	state;
	int			key_size;
	char		*key;
	char		*value;
	bool		keep_empty_word;

	buf = sbuf_init(1);
	if (!buf)
		return ;
	keep_empty_word = false;
	state = STATE_NORMAL;
	i = 0;
	while (input[i])
	{
		if (update_quote_state(&state, input[i]))
		{
			if (input[i] == '\'' || input[i] == '"')
				keep_empty_word = true;
			i++;
			continue ;
		}
		if (input[i] == '$' && state != STATE_IN_SQUOTE)
		{
			key_size = get_key_size(input, i);
			if (key_size != 0)
			{
				key = ft_substr(input, i + 1, key_size);
				value = get_value(env_list, exit_status, key);
				if (state == STATE_IN_DQUOTE)
				{
					keep_empty_word = true;
					sbuf_push_str(buf, value);
				}
				else
					handle_unquoted_expansion(expanded_words, buf, value);
				i += key_size + 1;
				free(key);
				free(value);
				continue;
			}
		}
		sbuf_push_char(buf, input[i]);
		i++;
	}
	if (buf->len > 0 || keep_empty_word)
		ft_lstadd_back(expanded_words, ft_lstnew(strdup(buf->data)));
	free_sbuf(buf);
}

char *expand_filename(char *input, t_env *env_list, int exit_status)
{
	char		*output;
	t_sbuf		*buf;
	int			i;
	t_str_state	state;
	int			key_size;
	char		*key;
	char		*value;

	buf = sbuf_init(1);
	if (!buf)
		return (NULL);
	state = STATE_NORMAL;
	i = 0;
	while (input[i])
	{
		if (update_quote_state(&state, input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '$' && state != STATE_IN_SQUOTE)
		{
			key_size = get_key_size(input, i);
			if (key_size != 0)
			{
				key = ft_substr(input, i + 1, key_size);
				value = get_value(env_list, exit_status, key);
				if (value)
					sbuf_push_str(buf, value);
				i += key_size + 1;
				free(key);
				free(value);
				continue;
			}
		}
		sbuf_push_char(buf, input[i]);
		i++;
	}
	output = strdup(buf->data);
	free_sbuf(buf);
	return (output);
}
