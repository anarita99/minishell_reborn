/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:34:34 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"
#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

static int	compare_token(t_token expected, t_token actual, int index)
{
	if (expected.type != actual.type)
	{
		printf("Token %d type mismatch: expected %d, got %d\n",
			index, expected.type, actual.type);
		return (0);
	}
	if (ft_strncmp(expected.value, actual.value, ft_strlen(expected.value)) != 0)
	{
		printf("Token %d value mismatch: expected '%s', got '%s'\n",
			index, expected.value, actual.value);
		return (0);
	}
	return (1);
}

static void	compare_lst(int token_count, t_token *head_actual, t_token *head_expected)
{
	t_token	*current_actual;
	t_token	*current_expected;
	
	// Compare
	int i = 0;
	int success = 1;
	current_actual = head_actual;
	current_expected = head_expected;
	while (current_actual && current_expected)
	{
		if (!compare_token(*current_expected, *current_actual, i))
			success = 0;
		current_actual = current_actual->next;
		current_expected = current_expected->next;
		i++;
	}
	
	// Check if both lists have the same length
	if (current_actual != NULL || current_expected != NULL || i != token_count)
	{
		printf("Token count mismatch: expected %d, got %d\n", token_count, i);
		success = 0;
	}
	
	// Free tokens
	free_tokens(head_actual);
	free_tokens(head_expected);

	if (success)
		print_passed();
	else
		print_failed();
	printf("\n");
}

/*
** Test 1: Simple command
** Input: "echo hello"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"]
*/
static void	test_simple_command(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo hello");
	token_count = 2;
	print_test_info(1, "Simple command", input);
	
	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("hello"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	
	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 2: Command with pipe
** Input: "ls | grep test"
** Expected: [T_WORD:"ls"] [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"]
*/
static void	test_pipe(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("ls | grep test");
	token_count = 4;
	print_test_info(2, "Command with pipe", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("ls"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("grep"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("test"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 3: Input redirection
** Input: "cat < input.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
*/
static void	test_input_redirection(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat < input.txt");
	token_count = 3;
	print_test_info(3, "Input redirection", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIR_IN, ft_strdup("<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("input.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 4: Output redirection
** Input: "echo hello > output.txt"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"] [T_REDIT_OUT:">"] [T_WORD:"output.txt"]
*/
static void	test_output_redirection(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo hello > output.txt");
	token_count = 4;
	print_test_info(4, "Output redirection", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("hello"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIT_OUT, ft_strdup(">"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("output.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 5: Heredoc
** Input: "cat << EOF"
** Expected: [T_WORD:"cat"] [T_HEREDOC:"<<"] [T_WORD:"EOF"]
*/
static void	test_heredoc(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat << EOF");
	token_count = 3;
	print_test_info(5, "Heredoc", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("hello"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIT_OUT, ft_strdup(">"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("output.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 6: Append redirection
** Input: "echo hello >> output.txt"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"] [T_APPEND:">>"] [T_WORD:"output.txt"]
*/
static void	test_append(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo hello >> output.txt");
	token_count = 4;
	print_test_info(6, "Append redirection", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("hello"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_APPEND, ft_strdup(">>"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("output.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 7: Quoted strings
** Input: "echo \"hello world\""
** Expected: [T_WORD:"echo"] [T_WORD:"hello world"]
*/
static void	test_quoted_strings(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo \"hello world\"");
	token_count = 2;
	print_test_info(7, "Quoted strings", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("hello world"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 8: Multiple pipes
** Input: "ls | grep test | wc -l"
** Expected: [T_WORD:"ls"] [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"] 
**           [T_PIPE:"|"] [T_WORD:"wc"] [T_WORD:"-l"]
*/
static void	test_multiple_pipes(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("ls | grep test | wc -l");
	token_count = 7;
	print_test_info(8, "Multiple pipes", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("ls"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("grep"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("test"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("wc"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("-l"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 9: Multiple redirections
** Input: "cat < input.txt > output.txt"
** Expected: 	[T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
** 				[T_REDIT_OUT:">"] [T_WORD:"output.txt"]
*/
static void	test_multiple_redirections(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat < input.txt > output.txt");
	token_count = 5;
	print_test_info(9, "Multiple redirections", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("input.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup(">"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("output.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 10: Empty input
** Input: ""
** Expected: NULL or empty token array
*/
static void	test_empty_input(void)
{
	t_token	*head_actual;
	char	*input;
	int		token_count;
	
	input = "";
	token_count = 0;
	print_test_info(10, "Empty input", input);

	// Actual Tokens
	head_actual = lexer(input);

	compare_lst(token_count, NULL, head_actual);
}

void	run_lexer_tests(void)
{
	printf("════════════════════ LEXER TESTS ════════════════════\n");
	printf("\n");
	
	test_simple_command();
	test_pipe();
	test_input_redirection();
	test_output_redirection();
	test_heredoc();
	test_append();
	test_quoted_strings();
	test_multiple_pipes();
	test_multiple_redirections();
	test_empty_input();
}
