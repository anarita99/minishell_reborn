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

// Lexer Only
int	    run_lexer_test(int test_num, char *name, char *input, 
	    t_token_type types[], char *values[], int token_count);

// Parser Only
int	    run_parser_test(int test_num, char *name, char *input, 
	    char *expected_argv[], int argc);

// Tests
int	    (**get_lexer_tests(void))(void);
int     (**get_parser_tests(void))(void);

// Utils
void	run_tests(char *module_name, int (**tests)(void));
void	print_test_info(int n, char *name, char *input);

#endif
