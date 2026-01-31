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
	if (!expected.value || !actual.value)
	{
		printf("Token %d value is NULL\n", index);
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

static int	compare_lst(int token_count, t_token *head_actual, t_token *head_expected)
{
	t_token	*current_actual;
	t_token	*current_expected;
	
	// Compare
	current_actual = head_actual;
	current_expected = head_expected;
	int success = 1;
	int i = 0;
	while (current_actual && current_expected)
	{
		if (!compare_token(*current_expected, *current_actual, i))
			success = 0;
		current_actual = current_actual->next;
		current_expected = current_expected->next;
		i++;
	}
	
	// Check if both lists have the same length
	if (current_actual || current_expected)
	{
		printf("Token count mismatch: expected %d, got %d\n", token_count, i);
		success = 0;
	}
	
	free_tokens(head_actual);
	free_tokens(head_expected);
	return (success);
}

static t_token	*build_expected_tokens(t_token_type types[], char *values[], int count)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < count)
	{
		token = create_token(types[i], ft_strdup(values[i]));
		add_token_to_list(&head, &tail, token);
		i++;
	}
	return (head);
}

static int	run_single_test(int test_num, char *name, char *input, 
	t_token_type types[], char *values[], int token_count)
{
	t_token	*head_actual;
	t_token	*head_expected;

	print_test_info(test_num, name, input);

	// Actual
	head_actual = lexer(input);

	// Expected
	if (token_count == 0)
		head_expected = NULL;
	else
		head_expected = build_expected_tokens(types, values, token_count);

	return (compare_lst(token_count, head_actual, head_expected));
}


/*
** Test 1: Simple command
** Input: "echo hello"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"]
*/
static int	test_simple_command(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "hello"};
	int				token_count = 2;
	
	return (run_single_test(1, "Simple command", "echo hello", 
		types, values, token_count));
}

/*
** Test 2: Command with pipe
** Input: "ls | grep test"
** Expected: [T_WORD:"ls"] [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"]
*/
static int	test_pipe(void)
{
	t_token_type	types[] = {T_WORD, T_PIPE, T_WORD, T_WORD};
	char			*values[] = {"ls", "|", "grep", "test"};
	int				token_count = 4;
	
	return (run_single_test(2, "Command with pipe", "ls | grep test",
		types, values, token_count));
}

/*
** Test 3: Input redirection
** Input: "cat < input.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
*/
static int	test_input_redirection(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD};
	char			*values[] = {"cat", "<", "input.txt"};
	int				token_count = 3;
	
	return (run_single_test(3, "Input redirection", "cat < input.txt",
		types, values, token_count));
}

/*
** Test 4: Output redirection
** Input: "echo hello > output.txt"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"] [T_REDIR_OUT:">"] [T_WORD:"output.txt"]
*/
static int	test_output_redirection(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"echo", "hello", ">", "output.txt"};
	int				token_count = 4;
	
	return (run_single_test(4, "Output redirection", "echo hello > output.txt",
		types, values, token_count));
}

/*
** Test 5: Heredoc
** Input: "cat << EOF"
** Expected: [T_WORD:"cat"] [T_HEREDOC:"<<"] [T_WORD:"EOF"]
*/
static int	test_heredoc(void)
{
	t_token_type	types[] = {T_WORD, T_HEREDOC, T_WORD};
	char			*values[] = {"cat", "<<", "EOF"};
	int				token_count = 3;
	
	return (run_single_test(5, "Heredoc", "cat << EOF",
		types, values, token_count));
}

/*
** Test 6: Append redirection
** Input: "echo hello >> output.txt"
** Expected: [T_WORD:"echo"] [T_WORD:"hello"] [T_APPEND:">>"] [T_WORD:"output.txt"]
*/
static int	test_append(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"echo", "hello", ">>", "output.txt"};
	int				token_count = 4;
	
	return (run_single_test(6, "Append redirection", "echo hello >> output.txt",
		types, values, token_count));
}

/*
** Test 7: Quoted strings
** Input: "echo \"hello world\""
** Expected: [T_WORD:"echo"] [T_WORD:""hello world""]
*/
static int	test_quoted_strings(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"hello world\""};
	int				token_count = 2;
	
	return (run_single_test(7, "Quoted strings", "echo \"hello world\"",
		types, values, token_count));
}

/*
** Test 8: Multiple pipes
** Input: "ls | grep test | wc -l"
** Expected: [T_WORD:"ls"] [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"] 
**           [T_PIPE:"|"] [T_WORD:"wc"] [T_WORD:"-l"]
*/
static int	test_multiple_pipes(void)
{
	t_token_type	types[] = {T_WORD, T_PIPE, T_WORD, T_WORD, T_PIPE, T_WORD, T_WORD};
	char			*values[] = {"ls", "|", "grep", "test", "|", "wc", "-l"};
	int				token_count = 7;
	
	return (run_single_test(8, "Multiple pipes", "ls | grep test | wc -l",
		types, values, token_count));
}

/*
** Test 9: Multiple redirections
** Input: "cat < input.txt > output.txt"
** Expected: 	[T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
** 				[T_REDIR_OUT:">"] [T_WORD:"output.txt"]
*/
static int	test_multiple_redirections(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"cat", "<", "input.txt", ">", "output.txt"};
	int				token_count = 5;
	
	return (run_single_test(9, "Multiple redirections", "cat < input.txt > output.txt",
		types, values, token_count));
}

/*
** Test 10: Empty input
** Input: ""
** Expected: NULL or empty token array
*/
static int	test_empty_input(void)
{
	return (run_single_test(10, "Empty input", "", NULL, NULL, 0));
}

/*
** Test 11: Single quotes with special characters
** Input: "echo 'hello|world'"
** Expected: [T_WORD:"echo"] [T_WORD:"'hello|world'"]
** Single quotes should prevent pipe interpretation
*/
static int	test_single_quotes_special_chars(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "'hello|world'"};
	int				token_count = 2;
	
	return (run_single_test(11, "Single quotes with special chars", "echo 'hello|world'",
		types, values, token_count));
}

/*
** Test 12: Single quotes with redirections
** Input: "cat 'file<>name.txt'"
** Expected: [T_WORD:"cat"] [T_WORD:"'file<>name.txt'"]
** Single quotes should prevent redirection operators interpretation
*/
static int	test_single_quotes_with_operators(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"cat", "'file<>name.txt'"};
	int				token_count = 2;
	
	return (run_single_test(12, "Single quotes with operators", "cat 'file<>name.txt'",
		types, values, token_count));
}

/*
** Test 13: Double quotes with environment variable
** Input: "echo \"$HOME\""
** Expected: [T_WORD:"echo"] [T_WORD:""$HOME""]
** Dollar sign should be preserved in double quotes for expansion
*/
static int	test_double_quotes_with_variable(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"$HOME\""};
	int				token_count = 2;
	
	return (run_single_test(13, "Double quotes with variable", "echo \"$HOME\"",
		types, values, token_count));
}

/*
** Test 14: Single quotes should NOT expand variables
** Input: "echo '$HOME'"
** Expected: [T_WORD:"echo"] [T_WORD:"'$HOME'"]
** Dollar sign should NOT be expanded in single quotes
*/
static int	test_single_quotes_no_expansion(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "'$HOME'"};
	int				token_count = 2;
	
	return (run_single_test(14, "Single quotes no expansion", "echo '$HOME'",
		types, values, token_count));
}

/*
** Test 15: Environment variable outside quotes
** Input: "echo $HOME"
** Expected: [T_WORD:"echo"] [T_WORD:"$HOME"]
** Lexer should preserve $VAR for later expansion
*/
static int	test_env_variable_unquoted(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$HOME"};
	int				token_count = 2;
	
	return (run_single_test(15, "Environment variable unquoted", "echo $HOME",
		types, values, token_count));
}

/*
** Test 16: Exit status variable
** Input: "echo $?"
** Expected: [T_WORD:"echo"] [T_WORD:"$?"]
** Should preserve $? for expansion
*/
static int	test_exit_status_variable(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$?"};
	int				token_count = 2;
	
	return (run_single_test(16, "Exit status variable", "echo $?",
		types, values, token_count));
}

/*
** Test 17: Mixed quotes
** Input: "echo 'hello' \"world\""
** Expected: [T_WORD:"echo"] [T_WORD:"'hello'"] [T_WORD:""world""]
*/
static int	test_mixed_quotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_WORD};
	char			*values[] = {"echo", "'hello'", "\"world\""};
	int				token_count = 3;
	
	return (run_single_test(17, "Mixed quotes", "echo 'hello' \"world\"",
		types, values, token_count));
}

/*
** Test 18: Heredoc with word
** Input: "cat << 'EOF'"
** Expected: [T_WORD:"cat"] [T_HEREDOC:"<<"] [T_WORD:"'EOF'"]
*/
static int	test_heredoc_quoted_delimiter(void)
{
	t_token_type	types[] = {T_WORD, T_HEREDOC, T_WORD};
	char			*values[] = {"cat", "<<", "'EOF'"};
	int				token_count = 3;
	
	return (run_single_test(18, "Heredoc with quoted delimiter", "cat << 'EOF'",
		types, values, token_count));
}

/*
** Test 19: Complex pipe with redirections
** Input: "cat < in.txt | grep test > out.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"in.txt"]
**           [T_PIPE:"|"] [T_WORD:"grep"] [T_WORD:"test"]
**           [T_REDIR_OUT:">"] [T_WORD:"out.txt"]
*/
static int	test_complex_pipe_redirections(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_PIPE, T_WORD, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"cat", "<", "in.txt", "|", "grep", "test", ">", "out.txt"};
	int				token_count = 8;
	
	return (run_single_test(19, "Complex pipe with redirections", "cat < in.txt | grep test > out.txt",
		types, values, token_count));
}

/*
** Test 20: Quotes in the middle of word
** Input: "he"l"lo'world'"
** Expected: [T_WORD:"helloworld"]
** Quotes should merge with surrounding text
*/
static int	test_quotes_in_middle_of_word(void)
{
	t_token_type	types[] = {T_WORD};
	char			*values[] = {"helloworld"};
	int				token_count = 1;
	
	return (run_single_test(20, "Quotes in middle of word", "he\"l\"lo'world'",
		types, values, token_count));
}

/*
** Test 21: Variable with underscore and numbers
** Input: "echo $USER_NAME_123"
** Expected: [T_WORD:"echo"] [T_WORD:"$USER_NAME_123"]
*/
static int	test_variable_with_underscore_and_numbers(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$USER_NAME_123"};
	int				token_count = 2;
	
	return (run_single_test(21, "Variable with underscore and numbers", "echo $USER_NAME_123",
		types, values, token_count));
}

/*
** Test 22: Consecutive redirections
** Input: "cat >> file1 >> file2"
** Expected: [T_WORD:"cat"] [T_APPEND:">>"] [T_WORD:"file1"]
**           [T_APPEND:">>"] [T_WORD:"file2"]
*/
static int	test_consecutive_append(void)
{
	t_token_type	types[] = {T_WORD, T_APPEND, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"cat", ">>", "file1", ">>", "file2"};
	int				token_count = 5;
	
	return (run_single_test(22, "Consecutive append redirections", "cat >> file1 >> file2",
		types, values, token_count));
}

/*
** Test 23: Pipe after quoted string
** Input: "echo \"hello\" | cat"
** Expected: [T_WORD:"echo"] [T_WORD:""hello""] [T_PIPE:"|"] [T_WORD:"cat"]
*/
static int	test_pipe_after_quoted_string(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_PIPE, T_WORD};
	char			*values[] = {"echo", "\"hello\"", "|", "cat"};
	int				token_count = 4;
	
	return (run_single_test(23, "Pipe after quoted string", "echo \"hello\" | cat",
		types, values, token_count));
}

/*
** Test 24: Multiple variables in double quotes
** Input: "echo \"$HOME/$USER\""
** Expected: [T_WORD:"echo"] [T_WORD:""$HOME/$USER""]
*/
static int	test_multiple_variables_in_quotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"$HOME/$USER\""};
	int				token_count = 2;
	
	return (run_single_test(24, "Multiple variables in double quotes", "echo \"$HOME/$USER\"",
		types, values, token_count));
}

/*
** Test 25: Redirection with no spaces
** Input: "cat<input.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"]
*/
static int	test_redirection_no_spaces(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD};
	char			*values[] = {"cat", "<", "input.txt"};
	int				token_count = 3;
	
	return (run_single_test(25, "Redirection with no spaces", "cat<input.txt",
		types, values, token_count));
}

/*
** Test 26: Redirection with no spaces (Alt)
** Input: "cat<input.txt|cat>>output.txt"
** Expected: [T_WORD:"cat"] [T_REDIR_IN:"<"] [T_WORD:"input.txt"] [T_PIPE:"|"] [T_WORD:"cat"] [T_APPEND:">>"] [T_WORD:"output.txt"]
*/
static int	test_redirection_no_spaces_alt(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_PIPE, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"cat", "<", "input.txt", "|", "cat", ">>", "output.txt"};
	int				token_count = 7;
	
	return (run_single_test(26, "Redirection with no spaces (Alt)", "cat<input.txt|cat>>output.txt",
		types, values, token_count));
}

void	run_lexer_tests(void)
{
	int	(*tests[])(void) = {
		test_simple_command,
		test_pipe,
		test_input_redirection,
		test_output_redirection,
		test_heredoc,
		test_append,
		test_quoted_strings,
		test_multiple_pipes,
		test_multiple_redirections,
		test_empty_input,
		test_single_quotes_special_chars,
		test_single_quotes_with_operators,
		test_double_quotes_with_variable,
		test_single_quotes_no_expansion,
		test_env_variable_unquoted,
		test_exit_status_variable,
		test_mixed_quotes,
		test_heredoc_quoted_delimiter,
		test_complex_pipe_redirections,
		test_quotes_in_middle_of_word,
		test_variable_with_underscore_and_numbers,
		test_consecutive_append,
		test_pipe_after_quoted_string,
		test_multiple_variables_in_quotes,
		test_redirection_no_spaces,
		test_redirection_no_spaces_alt
	};

	printf("════════════════════ LEXER TESTS ════════════════════\n");
	printf("\n");
	
	int	num_tests = sizeof(tests) / sizeof(tests[0]);
	int	success_count = 0;
	int	i = 0;
	while (i < num_tests)
	{
		if (tests[i]() == 1)
		{
			success_count++;
			print_passed();
		}
		else
			print_failed();
		printf("\n");
		i++;
	}
	print_passed_count(success_count, num_tests);
}
