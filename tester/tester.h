/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:26:35 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>
# include <string.h>
# include "../includes/minishell.h"

typedef struct s_test_info
{
	int		num;
	char	*name;
	char	*input;
} 			t_test_info;

// Lexer Only
int		compare_tokens(t_token *actual, t_token *expected, int count);
int		run_lexer_test(t_test_info info, t_token_type types[], char *values[], int count);

// Parser Only
void	build_expected_cmds(t_list **cmd_list, char **argv, t_redir *redirs);
int		compare_cmd_list(t_list *actual, t_list *expected);
int		run_parser_test(t_test_info info, t_list *head_expected);

// Tests
int	    (**get_lexer_tests(void))(void);
int     (**get_parser_tests(void))(void);

// Utils
void	run_tests(char *module_name, int (**tests)(void));
void	print_test_info(t_test_info info);

#endif