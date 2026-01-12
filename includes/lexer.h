/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:06:58 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 13:28:49 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// Token

t_token	*create_token(t_token_type type, char *value);
void	add_token_to_list(t_token **head, t_token **tail, t_token *token);
void	free_tokens(t_token *head);
void	print_tokens(t_token *head);

// Types

int	find_token_type(char *input, int idx);
t_token	*create_word(char *input, int start_idx, int end_idx);
t_token	*create_operator(t_token_type type, char *str);

#endif