/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:29 by leramos-          #+#    #+#             */
/*   Updated: 2026/04/13 11:16:35 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token(t_token *token, int n)
{
	printf("Token %i: ", n);
	if (token->type == T_WORD)
		printf("[WORD : ");
	else if (token->type == T_PIPE)
		printf("[PIPE : ");
	else if (token->type == T_REDIR_IN)
		printf("[REDIR_IN : ");
	else if (token->type == T_REDIR_OUT)
		printf("[REDIR_OUT : ");
	else if (token->type == T_HEREDOC)
		printf("[HEREDOC : ");
	else if (token->type == T_APPEND)
		printf("[APPEND : ");
	printf("%s]", token->value);
	printf("\n");
}

void	print_tokenlst(t_list *token_list)
{
	int		i;
	t_list	*current_node;
	t_token	*current_token;

	current_node = token_list;
	i = 0;
	while (current_node)
	{
		current_token = (t_token *)current_node->content;
		print_token(current_token, i);
		i++;
		current_node = current_node->next;
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