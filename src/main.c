/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/28 19:12:10 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	t_token		*token_head;

	sh_s()->env_list = init_env();
	sh_s()->exit_status = 0;
	while (1)
	{
		// 1 - Prompt
		input = readline("Minishell> ");
		if (!input || !input[0])
			exit_builtin(NULL);
		add_history(input);
		// 2 - Lexer
		printf("\n=== 1. Tokens ===\n");
		token_head = lexer(input);
		free(input);
		if (!token_head)
			return (1);
		print_tokens(token_head);
		printf("\n");
		// 3 - Syntax Checker
		if (!validate_tokens(token_head))
		{
			free_tokens(&token_head);
			continue ;
		}
		// 4 - Parser
		printf("\n=== 2. Parser CMDs ===\n");
		sh_s()->input_list = parser(token_head);
		free_tokens(&token_head);
		if (!sh_s()->input_list)
			return (1);
		print_cmdlst(sh_s()->input_list);
		printf("\n");
		// 5 - Expander
		printf("\n=== 3. Expander CMDs ===\n");
		expander(&(sh_s()->input_list), sh_s()->env_list);
		print_cmdlst(sh_s()->input_list);
		printf("\n");
		// 6 - Executor
		printf("\n=== 4. Result ===\n");
		executor();
		ft_lstclear(&sh_s()->input_list, del_cmd);
	}
	return (0);
}
