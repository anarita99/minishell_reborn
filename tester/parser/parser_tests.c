/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:34:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

/*
** Test 1: Simple command
** Input: "echo hello"
** Expected: 1 command with argv ["echo", "hello"]
*/
static int	test_simple_command(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "hello", NULL};
	t_redir	redirs[] = {{T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){1, "Simple command", "echo hello"}, cmd_list));
}

/*
** Test 2: Command with pipe
** Input: "ls | grep test"
** Expected: 2 commands - cmd1: [ls], cmd2: [grep, test]
*/
static int	test_pipe(void)
{
	t_list	*cmd_list;
	char	*argv1[] = {"ls", NULL};
	t_redir	redirs1[] = {{T_NONE, NULL, false}};
	char	*argv2[] = {"grep", "test", NULL};
	t_redir	redirs2[] = {{T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv1, redirs1);
	build_expected_cmds(&cmd_list, argv2, redirs2);
	return (run_parser_test((t_test_info){2, "Command with pipe", "ls | grep test"}, cmd_list));
}

/*
** Test 3: Command with input redirection
** Input: "cat < input.txt"
** Expected: 1 command with argv [cat] and input redirection to input.txt
*/
static int	test_input_redirection(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"cat", NULL};
	t_redir	redirs[] = {{T_REDIR_IN, "input.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){3, "Input redirection", "cat < input.txt"}, cmd_list));
}

/*
** Test 4: Command with output redirection
** Input: "echo hello > output.txt"
** Expected: 1 command with argv [echo, hello] and output redirection
*/
static int	test_output_redirection(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "hello", NULL};
	t_redir	redirs[] = {{T_REDIR_OUT, "output.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){4, "Output redirection", "echo hello > output.txt"}, cmd_list));
}

/*
** Test 5: Multiple pipes
** Input: "ls | grep test | wc -l"
** Expected: 3 commands
*/
static int	test_multiple_pipes(void)
{
	t_list	*cmd_list;
	char	*argv1[] = {"ls", NULL};
	t_redir	redirs1[] = {{T_NONE, NULL, false}};
	char	*argv2[] = {"grep", "test", NULL};
	t_redir	redirs2[] = {{T_NONE, NULL, false}};
	char	*argv3[] = {"wc", "-l", NULL};
	t_redir	redirs3[] = {{T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv1, redirs1);
	build_expected_cmds(&cmd_list, argv2, redirs2);
	build_expected_cmds(&cmd_list, argv3, redirs3);
	return (run_parser_test((t_test_info){5, "Multiple pipes", "ls | grep test | wc -l"}, cmd_list));
}

/*
** Test 6: Command with redirections and pipe
** Input: "cat < in.txt | grep test > out.txt"
** Expected: 2 commands with appropriate redirections
*/
static int	test_complex_pipe_redirections(void)
{
	t_list	*cmd_list;
	char	*argv1[] = {"cat", NULL};
	t_redir	redirs1[] = {{T_REDIR_IN, "in.txt", false}, {T_NONE, NULL, false}};
	char	*argv2[] = {"grep", "test", NULL};
	t_redir	redirs2[] = {{T_REDIR_OUT, "out.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv1, redirs1);
	build_expected_cmds(&cmd_list, argv2, redirs2);
	return (run_parser_test((t_test_info){6, "Complex pipe with redirections",
		"cat < in.txt | grep test > out.txt"}, cmd_list));
}

/*
** Test 7: Quoted arguments
** Input: "echo \"hello world\""
** Expected: 1 command with argv [echo, "hello world"]
*/
static int	test_quoted_arguments(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "\"hello world\"", NULL};
	t_redir	redirs[] = {{T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){7, "Quoted arguments", "echo \"hello world\""}, cmd_list));
}

/*
** Test 8: Append redirection
** Input: "echo hello >> output.txt"
** Expected: 1 command with append redirection
*/
static int	test_append_redirection(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "hello", NULL};
	t_redir	redirs[] = {{T_APPEND, "output.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){8, "Append redirection", "echo hello >> output.txt"}, cmd_list));
}

/*
** Test 9: Heredoc
** Input: "cat << EOF"
** Expected: 1 command with heredoc redirection
*/
static int	test_heredoc(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"cat", NULL};
	t_redir	redirs[] = {{T_HEREDOC, "EOF", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){9, "Heredoc", "cat << EOF"}, cmd_list));
}

/*
** Test 10: Command with arguments and flags
** Input: "ls -la | grep -v total"
** Expected: 2 commands with their respective arguments
*/
static int	test_complex_arguments(void)
{
	t_list	*cmd_list;
	char	*argv1[] = {"ls", "-la", NULL};
	t_redir	redirs1[] = {{T_NONE, NULL, false}};
	char	*argv2[] = {"grep", "-v", "total", NULL};
	t_redir	redirs2[] = {{T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv1, redirs1);
	build_expected_cmds(&cmd_list, argv2, redirs2);
	return (run_parser_test((t_test_info){10, "Complex arguments", "ls -la | grep -v total"}, cmd_list));
}

/*
** Test 11: More than one word token after operator
** Input: "echo hi < input.txt bye bye"
** Expected: Equivalent to "echo hi bye bye < input.txt"
*/
static int	test_words_after_op(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "hi", "bye", "bye", NULL};
	t_redir	redirs[] = {{T_REDIR_IN, "input.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){11, "More than one word after OP",
		"echo hi < input.txt bye bye"}, cmd_list));
}

/*
** Test 12: Multiple redirections (input and output)
** Input: "cat < input.txt > output.txt"
** Expected: 1 command with argv [cat], input redirection from input.txt, 
** and output redirection to output.txt
*/
static int	test_multiple_redirections(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"cat", NULL};
	t_redir	redirs[] = {{T_REDIR_IN, "input.txt", false},
		{T_REDIR_OUT, "output.txt", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){12, "Multiple redirections",
		"cat < input.txt > output.txt"}, cmd_list));
}

/*
** Test 13: Multiple output redirections
** Input: "echo hello > a > b > c"
** Expected: 1 command with argv [echo, hello] and output redirection to c 
** (last redirection should override previous ones)
*/
static int	test_multiple_output_redirections(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"echo", "hello", NULL};
	t_redir	redirs[] = {{T_REDIR_OUT, "a", false}, {T_REDIR_OUT, "b", false},
		{T_REDIR_OUT, "c", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){13, "Multiple output redirections",
		"echo hello > a > b > c"}, cmd_list));
}

/*
** Test 14: Multiple input redirections
** Input: "cat < a < b < c"
** Expected: 1 command with argv [cat] and input redirection from c
** (last redirection should override previous ones)
*/
static int	test_multiple_input_redirections(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"cat", NULL};
	t_redir	redirs[] = {{T_REDIR_IN, "a", false}, {T_REDIR_IN, "b", false},
		{T_REDIR_IN, "c", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){14, "Multiple input redirections",
		"cat < a < b < c"}, cmd_list));
}

/*
** Test 15: Redirection at the beginning
** Input: "< in cmd arg1"
** Expected: 1 command with argv [cmd, arg1] and input redirection from in
*/
static int	test_redirection_at_beginning(void)
{
	t_list	*cmd_list;
	char	*argv[] = {"cmd", "arg1", NULL};
	t_redir	redirs[] = {{T_REDIR_IN, "in", false}, {T_NONE, NULL, false}};

	cmd_list = NULL;
	build_expected_cmds(&cmd_list, argv, redirs);
	return (run_parser_test((t_test_info){15, "Redirection at beginning",
		"< in cmd arg1"}, cmd_list));
}

int	(**get_parser_tests(void))(void)
{
	static int	(*tests[])(void) = {
		test_simple_command,
		test_pipe,
		test_input_redirection,
		test_output_redirection,
		test_multiple_pipes,
		test_complex_pipe_redirections,
		test_quoted_arguments,
		test_append_redirection,
		test_heredoc,
		test_complex_arguments,
		test_words_after_op,
		test_multiple_redirections,
		test_multiple_output_redirections,
		test_multiple_input_redirections,
		test_redirection_at_beginning,
		NULL
	};
	return (tests);
}
