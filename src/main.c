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

#include "lexer.h"
#include "minishell.h"

int	main(void)
{
	char		*prompt;
	t_token		*token;

	// prompt = readline(NULL);
	prompt = ft_strdup("");
	printf("Prompt = '%s'\n", prompt);
	token = lexer(prompt);
	free(prompt);
	if (token)
	{
		print_tokens(token);
		free_tokens(token);
	}
	return (0);
}
