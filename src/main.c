/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/02/17 11:55:19 by adores           ###   ########.fr       */
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
			return (1); //fazer limpeza
		// 3 - Parser
		sh_s()->input_list = parser(token_head);
		free_tokens(&token_head);
		if (!sh_s()->input_list)
			return (1); //fazer limpeza
		executor();
		//print_cmdlst(cmd_list);
		//printf("\n");	
		// 4 - Expander
		// TO BE IMPLEMENTED
		ft_lstclear(&sh_s()->input_list, del_cmd);
	}
	return (0);
}
