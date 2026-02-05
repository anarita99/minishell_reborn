/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:02:29 by adores            #+#    #+#             */
/*   Updated: 2026/02/05 17:08:50 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	malloc_error()
{
	ft_putendl_fd("minishell: allocation error", 2);
	exitclean('1');
}

/// @brief For exiting and printing any kind of error.
/// If context & detail are NULL & err is set to false, nothing is printed
/// @param context what exactly failed, 
/// IE, malloc or a command such as cd
/// @param detail extra info as to what failed 
/// IE, a file that could not be opened
/// @param exit_code exit status the process will exit with
/// @param err flag used to print exact error message
/// if function sets errno upon failure
void	error_exit(char *context, char *detail, int exit_code, bool err)
{
	print_err(context, detail, err);
	exitclean(exit_code);
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
	free_env_list(sh_s()->env_list);  //vai ter de limpar mais coisas
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

void	free_arr(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}