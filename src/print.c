/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 15:55:56 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *head)
{
	int	i;
	t_token *current;

	current = head;
	i = 0;
	while (current)
	{
		printf("Token %i: ", i);
		if (current->type == T_WORD)
			printf("[WORD : ");
		else if (current->type == T_PIPE)
			printf("[PIPE : ");
		else if (current->type == T_REDIR_IN)
			printf("[REDIR_IN : ");
		else if (current->type == T_REDIR_OUT)
			printf("[REDIR_OUT : ");
		else if (current->type == T_HEREDOC)
			printf("[HEREDOC : ");
		else if (current->type == T_APPEND)
			printf("[APPEND : ");
		printf("%s]", current->value);
		printf("\n");
		i++;
		current = current->next;
	}
}

// - argv: [ls, -la]
// - argv: (none)
static void	print_argv(char **argv)
{
	int	i;

	printf("- argv: ");
	if (!argv)
	{
		printf("(none)\n");
		return ;
	}
	printf("[");
	i = 0;
	while (argv[i])
	{
		if (i > 0)
			printf(", ");
		printf("%s", argv[i]);
		i++;
	}
	printf("]\n");
}

// - redirs: [APPEND : output.txt : true] , 
// - redirs: (none)
static void	print_redirs(t_redir *redirs)
{
	int	i;

	printf("- redirs: ");
	i = 0;
	if (!redirs || redirs[i].type == T_NONE)
	{
		printf("(none)\n");
		return ;
	}
	while (redirs[i].type != T_NONE)
	{
		if (i > 0)
			printf(", ");
		printf("[");
		if (redirs[i].type == T_REDIR_IN)
			printf("REDIR_IN");
		if (redirs[i].type == T_REDIR_OUT)
			printf("REDIR_OUT");
		if (redirs[i].type == T_HEREDOC)
			printf("HEREDOC");
		if (redirs[i].type == T_APPEND)
			printf("APPEND");
		printf(" : %s : %s]", redirs[i].filename, redirs[i].quoted ? "true" : "false");
		i++;
	}
	printf("\n");
}

void	print_cmdlst(t_list *cmd_lst)
{
	int		i;
	t_list	*current;
	t_cmd	*cmd;

	current = cmd_lst;
	i = 0;
	while (current)
	{
		printf("Command %i:\n", i);
		cmd = (t_cmd *)current->content;
		print_argv(cmd->argv);
		print_redirs(cmd->redirs);
		i++;
		current = current->next;
	}
}
