/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/08 16:02:37 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	int		i;
	int		locked;
	int		start_idx;
	int		end_idx;
	char	*value;

	locked = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		if (ft_isalpha(input[i]))
		{
			if (locked = 0)
			{
				locked = 1;
				start_idx = i;
			}
		}
		if (locked && !ft_isalpha(input[i]))
		{
			end_idx = i - 1;
			locked = 0;
			
			value = malloc(sizeof(char) * end_idx - start_idx);
			create_token(T_WORD, value);
		}
		i++;
	}
}
