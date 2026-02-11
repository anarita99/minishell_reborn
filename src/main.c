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
	t_token		*token_head;
	t_list		*cmd_list;

	// 1 - Prompt
	// prompt = readline(NULL);
	// prompt = ft_strdup("ls -la | echo hello >> 'output.txt'");
	prompt = ft_strdup("echo hi < input.txt bye bye");
	printf("Prompt = '%s'\n", prompt);
	printf("\n");

	// 2 - Lexer
	token_head = lexer(prompt);
	free(prompt);
	if (!token_head)
		return (1);
	print_tokens(&token_head);
	printf("\n");

	// 3 - Parser
	cmd_list = parser(token_head);
	free_tokens(token_head);
	if (!cmd_list)
		return (1);
	print_cmdlst(cmd_list);
	printf("\n");
	
	// 4 - Expander
	// TO BE IMPLEMENTED
	ft_lstclear(&cmd_list, del_cmd);

	return (0);
}
