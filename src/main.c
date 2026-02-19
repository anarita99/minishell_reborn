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
	char		*input;
	t_token		*token_head;
	t_list		*cmd_list;

	while (1)
	{
		// 1 - Prompt
		input = readline("Minishell> ");
		// prompt = ft_strdup("ls -la | echo hello >> 'output.txt'");
		// prompt = ft_strdup("echo hi < input.txt bye bye");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break;
		// printf("Prompt = '%s'\n", input);
		// printf("\n");

		// 2 - Lexer
		token_head = lexer(input);
		free(input);
		if (!token_head)
			return (1);
		// print_tokens(token_head);
		// printf("\n");

		if (!validate_tokens(token_head))
		{
			free_tokens(&token_head);
			continue ;
		}

		// 3 - Parser
		cmd_list = parser(token_head);
		free_tokens(&token_head);
		if (!cmd_list)
			return (1);
		print_cmdlst(cmd_list);
		printf("\n");
		
		// 4 - Expander
		// TO BE IMPLEMENTED
		ft_lstclear(&cmd_list, del_cmd);
	}

	return (0);
}
