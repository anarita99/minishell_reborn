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

int	main(int argc, char **argv)
{
	printf("\n");
	printf("Minishell Tester\n");
	printf("\n");
	if (argc == 1)
	{
		run_lexer_tests();
		run_parser_tests();
		return (0);
	}
	else if (argc == 2)
	{
		if (ft_strncmp(argv[1], "lexer", 6) == 0)
			run_lexer_tests();
		else if (ft_strncmp(argv[1], "parser", 7) == 0)
			run_parser_tests();
		return (0);
	}
	printf("Usage: %s [lexer|parser]\n", argv[0]);
	return (1);
}
