/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/03/02 17:54:18 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

/*
** Test 1: Simple command
** Input: echo hello
** Expected: [WORD : echo] [WORD : hello]
*/
static int	test_simple_command(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "hello"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){1, "Simple command", "echo hello"},
		types, values, token_count));
}

/*
** Test 2: Command with pipe
** Input: ls | grep test
** Expected: [WORD : ls] [PIPE : |] [WORD : grep] [WORD : test]
*/
static int	test_pipe(void)
{
	t_token_type	types[] = {T_WORD, T_PIPE, T_WORD, T_WORD};
	char			*values[] = {"ls", "|", "grep", "test"};
	int				token_count = 4;
	
	return (run_lexer_test((t_test_info){2, "Command with pipe", "ls | grep test"},
		types, values, token_count));
}

/*
** Test 3: Input redirection
** Input: cat < input.txt
** Expected: [WORD : cat] [REDIR_IN : <] [WORD : input.txt]
*/
static int	test_input_redirection(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD};
	char			*values[] = {"cat", "<", "input.txt"};
	int				token_count = 3;
	
	return (run_lexer_test((t_test_info){3, "Input redirection", "cat < input.txt"},
		types, values, token_count));
}

/*
** Test 4: Output redirection
** Input: echo hello > output.txt
** Expected: [WORD : echo] [WORD : hello] [REDIR_OUT : >] [WORD : output.txt]
*/
static int	test_output_redirection(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"echo", "hello", ">", "output.txt"};
	int				token_count = 4;
	
	return (run_lexer_test((t_test_info){4, "Output redirection", "echo hello > output.txt"},
		types, values, token_count));
}

/*
** Test 5: Heredoc
** Input: cat << EOF
** Expected: [WORD : cat] [HEREDOC : <<] [WORD : EOF]
*/
static int	test_heredoc(void)
{
	t_token_type	types[] = {T_WORD, T_HEREDOC, T_WORD};
	char			*values[] = {"cat", "<<", "EOF"};
	int				token_count = 3;
	
	return (run_lexer_test((t_test_info){5, "Heredoc", "cat << EOF"},
		types, values, token_count));
}

/*
** Test 6: Append redirection
** Input: echo hello >> output.txt
** Expected: [WORD : echo] [WORD : hello] [APPEND : >>] [WORD : output.txt]
*/
static int	test_append(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"echo", "hello", ">>", "output.txt"};
	int				token_count = 4;
	
	return (run_lexer_test((t_test_info){6, "Append redirection", "echo hello >> output.txt"},
		types, values, token_count));
}

/*
** Test 7: Quoted strings
** Input: echo "hello world"
** Expected: [WORD : echo] [WORD : "hello world"]
*/
static int	test_quoted_strings(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"hello world\""};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){7, "Quoted strings", "echo \"hello world\""},
		types, values, token_count));
}

/*
** Test 8: Multiple pipes
** Input: ls | grep test | wc -l
** Expected: [WORD : ls] [PIPE : |] [WORD : grep] [WORD : test] [PIPE : |] [WORD : wc] [WORD : -l]
*/
static int	test_multiple_pipes(void)
{
	t_token_type	types[] = {T_WORD, T_PIPE, T_WORD, T_WORD, T_PIPE, T_WORD, T_WORD};
	char			*values[] = {"ls", "|", "grep", "test", "|", "wc", "-l"};
	int				token_count = 7;
	
	return (run_lexer_test((t_test_info){8, "Multiple pipes", "ls | grep test | wc -l"},
		types, values, token_count));
}

/*
** Test 9: Multiple redirections
** Input: cat < input.txt > output.txt
** Expected: [WORD : cat] [REDIR_IN : <] [WORD : input.txt] [REDIR_OUT : >] [WORD : output.txt]
*/
static int	test_multiple_redirections(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"cat", "<", "input.txt", ">", "output.txt"};
	int				token_count = 5;
	
	return (run_lexer_test((t_test_info){9, "Multiple redirections", "cat < input.txt > output.txt"},
		types, values, token_count));
}

/*
** Test 10: Empty input
** Input: 
** Expected: NULL or empty token array
*/
static int	test_empty_input(void)
{
	return (run_lexer_test((t_test_info){10, "Empty input", ""}, NULL, NULL, 0));
}

/*
** Test 11: Single quotes with special characters
** Input: echo 'hello|world'
** Expected: [WORD : echo] [WORD : 'hello|world']
*/
static int	test_single_quotes_special_chars(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "'hello|world'"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){11, "Single quotes with special chars", "echo 'hello|world'"},
		types, values, token_count));
}

/*
** Test 12: Single quotes with redirections
** Input: cat 'file<>name.txt'
** Expected: [WORD : cat] [WORD : 'file<>name.txt']
*/
static int	test_single_quotes_with_operators(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"cat", "'file<>name.txt'"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){12, "Single quotes with operators", "cat 'file<>name.txt'"},
		types, values, token_count));
}

/*
** Test 13: Double quotes with environment variable
** Input: echo "$HOME\"
** Expected: [WORD : echo] [WORD : "$HOME"]
*/
static int	test_double_quotes_with_variable(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"$HOME\""};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){13, "Double quotes with variable", "echo \"$HOME\""},
		types, values, token_count));
}

/*
** Test 14: Single quotes with environment variable
** Input: echo '$HOME'
** Expected: [WORD : echo] [WORD : '$HOME']
*/
static int	test_single_quotes_with_variable(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "'$HOME'"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){14, "Single quotes with variable", "echo '$HOME'"},
		types, values, token_count));
}

/*
** Test 15: Environment variable outside quotes
** Input: echo $HOME
** Expected: [WORD : echo] [WORD : $HOME]
*/
static int	test_env_variable_unquoted(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$HOME"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){15, "Environment variable unquoted", "echo $HOME"},
		types, values, token_count));
}

/*
** Test 16: Exit status variable
** Input: echo $?
** Expected: [WORD : echo] [WORD : $?]
*/
static int	test_exit_status_variable(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$?"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){16, "Exit status variable", "echo $?"},
		types, values, token_count));
}

/*
** Test 17: Mixed quotes
** Input: echo 'hello' "world"
** Expected: [WORD : echo] [WORD : 'hello'] [WORD : "world"]
*/
static int	test_mixed_quotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_WORD};
	char			*values[] = {"echo", "'hello'", "\"world\""};
	int				token_count = 3;
	
	return (run_lexer_test((t_test_info){17, "Mixed quotes", "echo 'hello' \"world\""},
		types, values, token_count));
}

/*
** Test 18: Heredoc with word
** Input: cat << 'EOF'
** Expected: [WORD : cat] [HEREDOC : <<] [WORD : 'EOF']
*/
static int	test_heredoc_quoted_delimiter(void)
{
	t_token_type	types[] = {T_WORD, T_HEREDOC, T_WORD};
	char			*values[] = {"cat", "<<", "'EOF'"};
	int				token_count = 3;
	
	return (run_lexer_test((t_test_info){18, "Heredoc with quoted delimiter", "cat << 'EOF'"},
		types, values, token_count));
}

/*
** Test 19: Complex pipe with redirections
** Input: cat < in.txt | grep test > out.txt
** Expected: [WORD : cat] [REDIR_IN : <] [WORD : in.txt]
**           [PIPE : |] [WORD : grep] [WORD : test]
**           [REDIR_OUT : >] [WORD : out.txt]
*/
static int	test_complex_pipe_redirections(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_PIPE, T_WORD, T_WORD, T_REDIR_OUT, T_WORD};
	char			*values[] = {"cat", "<", "in.txt", "|", "grep", "test", ">", "out.txt"};
	int				token_count = 8;
	
	return (run_lexer_test((t_test_info){19, "Complex pipe with redirections", "cat < in.txt | grep test > out.txt"},
		types, values, token_count));
}

/*
** Test 20: Quotes in the middle of word
** Input: he"l"lo'world'
** Expected: [WORD : he"l"lo'world']
*/
static int	test_quotes_in_middle_of_word(void)
{
	t_token_type	types[] = {T_WORD};
	char			*values[] = {"he\"l\"lo'world'"};
	int				token_count = 1;
	
	return (run_lexer_test((t_test_info){20, "Quotes in middle of word", "he\"l\"lo'world'"},
		types, values, token_count));
}

/*
** Test 21: Variable with underscore and numbers
** Input: echo $USER_NAME_123
** Expected: [WORD : echo] [WORD : $USER_NAME_123]
*/
static int	test_variable_with_underscore_and_numbers(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "$USER_NAME_123"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){21, "Variable with underscore and numbers", "echo $USER_NAME_123"},
		types, values, token_count));
}

/*
** Test 22: Consecutive redirections
** Input: cat >> file1 >> file2
** Expected: [WORD : cat] [APPEND : >>] [WORD : file1] [APPEND : >>] [WORD : file2]
*/
static int	test_consecutive_append(void)
{
	t_token_type	types[] = {T_WORD, T_APPEND, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"cat", ">>", "file1", ">>", "file2"};
	int				token_count = 5;
	
	return (run_lexer_test((t_test_info){22, "Consecutive append redirections", "cat >> file1 >> file2"},
		types, values, token_count));
}

/*
** Test 23: Pipe after quoted string
** Input: echo "hello" | cat
** Expected: [WORD : echo] [WORD : "hello"] [PIPE : |] [WORD : cat]
*/
static int	test_pipe_after_quoted_string(void)
{
	t_token_type	types[] = {T_WORD, T_WORD, T_PIPE, T_WORD};
	char			*values[] = {"echo", "\"hello\"", "|", "cat"};
	int				token_count = 4;
	
	return (run_lexer_test((t_test_info){23, "Pipe after quoted string", "echo \"hello\" | cat"},
		types, values, token_count));
}

/*
** Test 24: Multiple variables in double quotes
** Input: echo "$HOME/$USER"
** Expected: [WORD : echo] [WORD : "$HOME/$USER"]
*/
static int	test_multiple_variables_in_quotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"$HOME/$USER\""};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){24, "Multiple variables in double quotes", "echo \"$HOME/$USER\""},
		types, values, token_count));
}

/*
** Test 25: Redirection with no spaces
** Input: cat<input.txt
** Expected: [WORD : cat] [REDIR_IN : <] [WORD : input.txt]
*/
static int	test_redirection_no_spaces(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD};
	char			*values[] = {"cat", "<", "input.txt"};
	int				token_count = 3;
	
	return (run_lexer_test((t_test_info){25, "Redirection with no spaces", "cat<input.txt"},
		types, values, token_count));
}

/*
** Test 26: Redirection with no spaces (Alt)
** Input: cat<input.txt|cat>>output.txt
** Expected: [WORD : cat] [REDIR_IN : <] [WORD : input.txt] [PIPE : |] [WORD : cat] [APPEND : >>] [WORD : output.txt]
*/
static int	test_redirection_no_spaces_alt(void)
{
	t_token_type	types[] = {T_WORD, T_REDIR_IN, T_WORD, T_PIPE, T_WORD, T_APPEND, T_WORD};
	char			*values[] = {"cat", "<", "input.txt", "|", "cat", ">>", "output.txt"};
	int				token_count = 7;
	
	return (run_lexer_test((t_test_info){26, "Redirection with no spaces (Alt)", "cat<input.txt|cat>>output.txt"},
		types, values, token_count));
}

/*
** Test 27: A lot of quotes
** Input: echo "he"l"lo'world'"
** Expected: [WORD : echo] [WORD : "he"l"lo'world'"]
*/
static int	test_lot_of_quotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "\"he\"l\"lo'world'\""};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){27, "A lot of quotes", "echo \"he\"l\"lo'world'\""},
		types, values, token_count));
}

/*
** Test 28: Random double quotes
** Input: echo hello"w"orld
** Expected: [WORD : echo] [WORD : hello"w"orld]
*/
static int	test_random_dquotes(void)
{
	t_token_type	types[] = {T_WORD, T_WORD};
	char			*values[] = {"echo", "hello\"w\"orld"};
	int				token_count = 2;
	
	return (run_lexer_test((t_test_info){28, "Random double quotes", "echo hello\"w\"orld"},
		types, values, token_count));
}

int	(**get_lexer_tests(void))(void)
{
	static int	(*tests[])(void) = {
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
		test_single_quotes_with_variable,
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
		test_redirection_no_spaces_alt,
		test_lot_of_quotes,
		test_random_dquotes,
		NULL
	};
	return (tests);
}
