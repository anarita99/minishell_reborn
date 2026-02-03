/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:02:29 by adores            #+#    #+#             */
/*   Updated: 2026/01/26 12:16:04 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	malloc_error()
{
	ft_putendl_fd("minishell: allocation error", 2);
	exitclean('1');
}

/// @brief For printing any kind of error. 
///If context & detail are NULL & err is set to false, nothing is printed
/// @param context what exactly failed, IE, malloc or a command such as cd
/// @param detail extra info as to what failed
/// IE, a file that could not be opened
/// @param err flag used to print exact error message
/// if function sets errno upon failure
void	print_err(char *context, char *detail, bool err)
{
	if (context || detail || err)
	{
		ft_putstr_fd("minishell: ", 2);
		if (context)
		{
			ft_putstr_fd(context, 2);
			ft_putstr_fd(": ", 2);
		}
		if (detail && err)
			perror(detail);
		else if (detail)
 			ft_putendl_fd(detail, 2);
		else if (err)
			ft_putendl_fd(strerror(errno), 2);
	}
}

void	exitclean(unsigned char exit_code)
{
	free_env_list(call_sh_struct()->env_list);  //vai ter de limpar mais coisas
	exit(exit_code);
}

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void free_env_list(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free_node(head);
		head = next;
	}
}

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
		free(str[--i]);
	free(str);
}
