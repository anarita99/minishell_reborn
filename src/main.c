/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/20 14:29:50 by leramos-         ###   ########.fr       */
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
		token_head = lexer(input);
		free(input);
		if (!token_head)
			return (1);
		if (!validate_tokens(token_head))
		{
			free_tokens(&token_head);
			continue ;
		}
		// 3 - Parser
		sh_s()->input_list = parser(token_head);
		free_tokens(&token_head);
		if (!sh_s()->input_list)
			return (1);
		//print_cmdlst(cmd_list);
		//printf("\n");
		// 4 - Expander
		// TO BE IMPLEMENTED
		;

		// 5 - Executor
		executor();
		ft_lstclear(&sh_s()->input_list, del_cmd);
	}
	return (0);
}
