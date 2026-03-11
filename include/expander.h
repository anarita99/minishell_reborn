/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 20:54:31 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/11 15:02:30 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "shared.h"
# include "parser.h"
# include "lexer.h"
# include "execution.h"

// Utils
int     update_quote_state(t_str_state *state, char c);
int	    get_key_size(char *str, int i);
char    *get_value(t_env *env_list, int exit_status, char *key);
bool	has_quotes(char *str);
void	remove_from_array(char **array, int index);

// Counter
int counter(t_env *env_list, int exit_status, char *str);

// Expand
char	*expand(t_env *env_list, int exit_status, char *str, int size);

// Main expander function
void	expander(t_list **commands, t_env *env_list, int exit_status);

#endif
