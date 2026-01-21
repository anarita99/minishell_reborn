/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/15 15:22:05 by leramos-         ###   ########.fr       */
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
	if (strcmp(expected.value, actual.value) != 0)
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
		success = compare_token(*current_expected, *current_actual, i);
		current_actual = current_actual->next;
		current_expected = current_expected->next;
		i++;
	}
	
	// Check if both lists have the same length
	if (i != token_count)
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
** Expected: [T_WORD:"echo"] [T_WORD:"hello"] [T_REDIR_OUT:">"] [T_WORD:"output.txt"]
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
	tmp = create_token(T_REDIR_OUT, ft_strdup(">"));
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
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_HEREDOC, ft_strdup("<<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("EOF"));
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
** Expected: [T_WORD:"echo"] [T_WORD:""hello world""]
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
	tmp = create_token(T_WORD, ft_strdup("\"hello world\""));
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
** 				[T_REDIR_OUT:">"] [T_WORD:"output.txt"]
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
	tmp = create_token(T_REDIR_IN, ft_strdup("<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("input.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIR_OUT, ft_strdup(">"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("output.txt"));
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

	compare_lst(token_count, head_actual, NULL);
}

/*
** Test 11: Single quotes with special characters
** Input: "echo 'hello|world'"
** Expected: [T_WORD:"echo"] [T_WORD:"'hello|world'"]
** Single quotes should prevent pipe interpretation
*/
static void	test_single_quotes_special_chars(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo 'hello|world'");
	token_count = 2;
	print_test_info(11, "Single quotes with special chars", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("'hello|world'"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 12: Single quotes with redirections
** Input: "cat 'file<>name.txt'"
** Expected: [T_WORD:"cat"] [T_WORD:"'file<>name.txt'"]
** Single quotes should prevent redirection operators interpretation
*/
static void	test_single_quotes_with_operators(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat 'file<>name.txt'");
	token_count = 2;
	print_test_info(12, "Single quotes with operators", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("'file<>name.txt'"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 13: Double quotes with environment variable
** Input: "echo \"$HOME\""
** Expected: [T_WORD:"echo"] [T_WORD:""$HOME""]
** Dollar sign should be preserved in double quotes for expansion
*/
static void	test_double_quotes_with_variable(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo \"$HOME\"");
	token_count = 2;
	print_test_info(13, "Double quotes with variable", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("\"$HOME\""));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 14: Single quotes should NOT expand variables
** Input: "echo '$HOME'"
** Expected: [T_WORD:"echo"] [T_WORD:"'$HOME'"]
** Dollar sign should NOT be expanded in single quotes
*/
static void	test_single_quotes_no_expansion(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo '$HOME'");
	token_count = 2;
	print_test_info(14, "Single quotes no expansion", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("'$HOME'"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 15: Environment variable outside quotes
** Input: "echo $HOME"
** Expected: [T_WORD:"echo"] [T_WORD:"$HOME"]
** Lexer should preserve $VAR for later expansion
*/
static void	test_env_variable_unquoted(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo $HOME");
	token_count = 2;
	print_test_info(15, "Environment variable unquoted", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("$HOME"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 16: Exit status variable
** Input: "echo $?"
** Expected: [T_WORD:"echo"] [T_WORD:"$?"]
** Should preserve $? for expansion
*/
static void	test_exit_status_variable(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo $?");
	token_count = 2;
	print_test_info(16, "Exit status variable", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("$?"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 17: Mixed quotes
** Input: "echo 'hello' \"world\""
** Expected: [T_WORD:"echo"] [T_WORD:"'hello'"] [T_WORD:""world""]
*/
static void	test_mixed_quotes(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo 'hello' \"world\"");
	token_count = 3;
	print_test_info(17, "Mixed quotes", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("'hello'"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("\"world\""));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 18: Heredoc with word
** Input: "cat << 'EOF'"
** Expected: [T_WORD:"cat"] [T_HEREDOC:"<<"] [T_WORD:"'EOF'"]
*/
static void	test_heredoc_quoted_delimiter(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat << 'EOF'");
	token_count = 3;
	print_test_info(18, "Heredoc with quoted delimiter", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_HEREDOC, ft_strdup("<<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("'EOF'"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 19: Complex pipe with redirections
** Input: "cat < in.txt | grep test > out.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"in.txt"]
**           [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"]
**           [T_REDIR_OUT:">"] [T_WORD:"out.txt"]
*/
static void	test_complex_pipe_redirections(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat < in.txt | grep test > out.txt");
	token_count = 8;
	print_test_info(19, "Complex pipe with redirections", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIR_IN, ft_strdup("<"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("in.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("grep"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("test"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_REDIR_OUT, ft_strdup(">"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("out.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 20: Quotes in the middle of word
** Input: "hello'world'"
** Expected: [T_WORD:"helloworld"]
** Quotes should merge with surrounding text
*/
static void	test_quotes_in_middle_of_word(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("hello'world'");
	token_count = 1;
	print_test_info(20, "Quotes in middle of word", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("helloworld"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 21: Variable with underscore and numbers
** Input: "echo $USER_NAME_123"
** Expected: [T_WORD:"echo"] [T_WORD:"$USER_NAME_123"]
*/
static void	test_variable_with_underscore_and_numbers(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo $USER_NAME_123");
	token_count = 2;
	print_test_info(21, "Variable with underscore and numbers", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("$USER_NAME_123"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 22: Consecutive redirections
** Input: "cat >> file1 >> file2"
** Expected: [T_WORD:"cat"] [T_APPEND:">>"] [T_WORD:"file1"]
**           [T_APPEND:">>"] [T_WORD:"file2"]
*/
static void	test_consecutive_append(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat >> file1 >> file2");
	token_count = 5;
	print_test_info(22, "Consecutive append redirections", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_APPEND, ft_strdup(">>"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("file1"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_APPEND, ft_strdup(">>"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("file2"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 23: Pipe after quoted string
** Input: "echo \"hello\" | cat"
** Expected: [T_WORD:"echo"] [T_WORD:""hello""] [T_PIPE:"|"] [T_WORD:"cat"]
*/
static void	test_pipe_after_quoted_string(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo \"hello\" | cat");
	token_count = 4;
	print_test_info(23, "Pipe after quoted string", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("\"hello\""));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 24: Multiple variables in double quotes
** Input: "echo \"$HOME/$USER\""
** Expected: [T_WORD:"echo"] [T_WORD:""$HOME/$USER""]
*/
static void	test_multiple_variables_in_quotes(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("echo \"$HOME/$USER\"");
	token_count = 2;
	print_test_info(24, "Multiple variables in double quotes", input);

	// Actual Tokens
	head_actual = lexer(input);

	// Expected Tokens
	head_expected = NULL;
	tail_expected = NULL;
	tmp = create_token(T_WORD, ft_strdup("echo"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("\"$HOME/$USER\""));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
}

/*
** Test 25: Redirection with no spaces
** Input: "cat<input.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
*/
static void	test_redirection_no_spaces(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat<input.txt");
	token_count = 3;
	print_test_info(25, "Redirection with no spaces", input);

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
** Test 26: Redirection with no spaces (Alt)
** Input: "cat<input.txt|cat>>output.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"] [T_PIPE:"|"] [T_WORD:"cat"] [T_APPEND:">>"] [T_WORD:"output.txt"]
*/
static void	test_redirection_no_spaces_alt(void)
{
	t_token	*head_actual;
	t_token	*head_expected;
	t_token	*tail_expected;
	t_token *tmp;
	char	*input;
	int		token_count;
	
	input = strdup("cat<input.txt|cat>>output.txt");
	token_count = 7;
	print_test_info(26, "Redirection with no spaces", input);

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
	tmp = create_token(T_PIPE, ft_strdup("|"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("cat"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_APPEND, ft_strdup(">>"));
	add_token_to_list(&head_expected, &tail_expected, tmp);
	tmp = create_token(T_WORD, ft_strdup("output.txt"));
	add_token_to_list(&head_expected, &tail_expected, tmp);

	compare_lst(token_count, head_actual, head_expected);
	free(input);
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
	test_single_quotes_special_chars();
	test_single_quotes_with_operators();
	test_double_quotes_with_variable();
	test_single_quotes_no_expansion();
	test_env_variable_unquoted();
	test_exit_status_variable();
	test_mixed_quotes();
	test_heredoc_quoted_delimiter();
	test_complex_pipe_redirections();
	test_quotes_in_middle_of_word();
	test_variable_with_underscore_and_numbers();
	test_consecutive_append();
	test_pipe_after_quoted_string();
	test_multiple_variables_in_quotes();
	test_redirection_no_spaces();
	test_redirection_no_spaces_alt();
}
