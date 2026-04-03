/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:01:32 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/03 14:19:19 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	handle_quotes(char c, t_str_state *state, t_sbuf *buf, bool *keep_empty_word)
{
	*keep_empty_word = true;
	if (*state == STATE_NORMAL)
	{
		if (c == '\'')
			*state = STATE_IN_SQUOTE;
		else if ((c == '\"'))
			*state = STATE_IN_DQUOTE;
	}
	else if ((*state == STATE_IN_SQUOTE && c == '\'')
		|| (*state == STATE_IN_DQUOTE && c == '\"'))
		*state = STATE_NORMAL;
	else
		sbuf_push_char(buf, c);
}

// words_head = NULL
// buf = pre
// value = ls -l
// result = prels, -l
static void	handle_unquoted_expansion(
	t_list **words_head, t_sbuf *buf, char *value)
{
	char	**value_split;
	int		i;

	if (!value)
		return ;
	value_split = ft_split_ws(value);
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
			ft_lstadd_back(words_head, ft_lstnew(strdup(value_split[i])));
		i++;
	}
	ft_freearray(value_split);
}

static void	handle_dollar_expansion(
	t_list **expanded_words, char *input, t_expander_ctx *ctx, int *i, bool is_argv)
{
	int		key_size;
	char	*key;
	char	*value;

	key_size = get_key_size(input, *i);
	if (key_size == 0)
	{
		sbuf_push_char(ctx->buf, input[*i]);
		return ;
	}
	key = ft_substr(input, *i + 1, key_size);
	value = get_value(ctx->env_list, ctx->status, key);
	if (ctx->state == STATE_IN_DQUOTE || !is_argv)
	{
		ctx->keep_empty_word = true;
		if (value)
			sbuf_push_str(ctx->buf, value);
	}
	else
		handle_unquoted_expansion(expanded_words, ctx->buf, value);
	*i += key_size;
	free(key);
	free(value);
}

t_expander_ctx	init_expander_ctx(t_env *env_list, int status)
{
	t_expander_ctx	ctx;

	ctx.buf = sbuf_init(1);
	ctx.env_list = env_list;
	ctx.status = status;
	ctx.keep_empty_word = false;
	ctx.state = STATE_NORMAL;
	return (ctx);
}

t_list	*expand_input(char *input, t_env *env_list, int status, bool is_argv, bool is_heredoc)
{
	t_list			*words;
	t_expander_ctx	ctx;
	int				i;

	words = NULL;
	ctx = init_expander_ctx(env_list, status);
	i = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && !is_heredoc)
			handle_quotes(input[i], &ctx.state, ctx.buf, &ctx.keep_empty_word);
		else if (input[i] == '$' && ctx.state != STATE_IN_SQUOTE)
			handle_dollar_expansion(&words, input, &ctx, &i, is_argv);
		else
			sbuf_push_char(ctx.buf, input[i]);
		i++;
	}
	if (ctx.buf->len > 0 || ctx.keep_empty_word)
		ft_lstadd_back(&words, ft_lstnew(strdup(ctx.buf->data)));
	sbuf_free(ctx.buf);
	return (words);
}
