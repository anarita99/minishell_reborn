/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 13:18:30 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	main(void)
{
	printf("\n");
	printf("Minishell Tester\n");
	printf("\n");
	run_tests("LEXER", get_lexer_tests());
	run_tests("PARSER", get_parser_tests());
	return (0);
}
