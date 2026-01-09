/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/09 13:56:52 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*prompt;
	t_token		*token;

	prompt = readline(NULL);
	printf("Prompt = '%s'\n", prompt);
	token = lexer(prompt);
	free(prompt);
	print_tokens(token);
	return (0);
}
