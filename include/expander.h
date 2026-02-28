/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:31 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 18:51:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "shared.h"
# include "parser.h"
# include "lexer.h"
# include "execution.h"

// Utils
char	*get_env_key(char *str, int *i);
void	remove_empty_str(char **array);

// Counter
int counter(t_env *env_list, char *str);

// Expand
char	*expand(t_env *env_list, char *str, int size);

// Main expander function
void	expander(t_list **commands, t_env *env_list);

#endif
