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
# include "../includes/lexer.h"

// Tests
void	run_lexer_tests(void);
void	run_parser_tests(void);

// Utils
void	print_test_info(int n, char *name, char *input);
void	print_passed(void);
void	print_failed(void);
void	print_passed_count(int count, int max);

#endif
