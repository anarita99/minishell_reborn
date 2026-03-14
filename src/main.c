/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/14 15:20:57 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	t_token		*token_head;
	bool		print_info;

	print_info = false;
	sh_s()->env_list = init_env();
	sh_s()->exit_status = 0;
	sh_s()->is_child = false;
	sh_s()->pids = NULL;
	sh_s()->prev_read = -1;
	while (1)
	{
		// 1 - Prompt
		input = readline("Minishell> ");
		if (!input || !input[0])
			exit_builtin(NULL);
		add_history(input);
		// 2 - Lexer
		if (print_info)
			printf("\n=== 1. Tokens ===\n");
		token_head = lexer(input);
		free(input);
		if (!token_head)
			continue ;
		if (print_info)
		{
			print_tokens(token_head);
			printf("\n");
		}
		// 3 - Syntax Checker
		if (!validate_tokens(token_head))
		{
			free_tokens(&token_head);
			continue ;
		}
		// 4 - Parser
		if (print_info)
			printf("\n=== 2. Parser CMDs ===\n");
		sh_s()->input_list = parser(token_head);
		free_tokens(&token_head);
		if (!sh_s()->input_list)
			continue ;
		if (print_info)
		{
			print_cmdlst(sh_s()->input_list);
			printf("\n");
		}
		// 5 - Expander
		if (print_info)
			printf("\n=== 3. Expander CMDs ===\n");
		expander(&(sh_s()->input_list), sh_s()->env_list, sh_s()->exit_status);
		if (print_info)
		{
			print_cmdlst(sh_s()->input_list);
			printf("\n");
		}
		// 6 - Executor
		if (print_info)
			printf("\n=== 4. Result ===\n");
		executor();
		ft_lstclear(&sh_s()->input_list, del_cmd);
		sh_s()->prev_read = -1;
	}
	return (0);
}
