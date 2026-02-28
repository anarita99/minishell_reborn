/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:59:30 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 18:52:39 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// alas$var what -> input: $var what
// strictly alphanumeric characters and underscores, with the caveat that it cannot start with a digit.
char	*get_env_key(char *str, int *i)
{
	int	start;
	int	len;

	if (!str || !i)
		return (NULL);
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] != '$')
		return (NULL);
	if (!str[*i + 1] || !(ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'))
		return (NULL);
	start = *i + 1;
	*i = start;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	(*i)--;
	return (ft_substr(str, start, len));
}

void	remove_empty_str(char **array)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (array[i])
	{
		str = array[i];
		if (str[0] == '\0')
		{
			free(str);
			j = i;
			while (array[j])
			{
				array[j] = array[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}