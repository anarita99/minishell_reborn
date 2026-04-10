/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:06:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/10 12:52:37 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*sh_s(void)
{
	static t_shell	shell;

	return (&shell);
}

static void	init_sh_s(void)
{
	sh_s()->env_list = init_env();
	sh_s()->exit_status = 0;
	sh_s()->is_child = false;
	sh_s()->pids = NULL;
	sh_s()->prev_read = -1;
}

static char	*get_input(void)
{
	char	*input;

	input = readline("Minishell> ");
	if (!input)
		exitclean((unsigned char)sh_s()->exit_status);
	return (input);
}

int	main(void)
{
	char		*input;
	t_list		*token_list;

	init_sh_s();
	while (1)
	{
		setup_signals();
		input = get_input();
		if (!input || !input[0])
			exitclean((unsigned char)sh_s()->exit_status);
		add_history(input);
		token_list = lexer(input);
		free(input);
		if (!token_list)
			continue ;
		sh_s()->input_list = parser(token_list);
		ft_lstclear(&token_list, del_token);
		if (!sh_s()->input_list)
			continue ;
		expander(&(sh_s()->input_list));
		executor();
		ft_lstclear(&sh_s()->input_list, del_cmd);
		sh_s()->prev_read = -1;
	}
	return (0);
}
