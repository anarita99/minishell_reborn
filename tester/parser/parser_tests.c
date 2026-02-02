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
	char	*argv[] = {"echo", "hello", NULL};
	int		argc = 2;
	return (run_parser_test(1, "Simple command", "echo hello", argv, argc));
}

/*
** Test 2: Command with pipe
** Input: "ls | grep test"
** Expected: 2 commands - cmd1: [ls], cmd2: [grep, test]
*/
static int	test_pipe(void)
{
	char	*argv[] = {"ls", NULL};
	int		argc = 1;
	return (run_parser_test(2, "Command with pipe", "ls | grep test", argv, argc));
}

/*
** Test 3: Command with input redirection
** Input: "cat < input.txt"
** Expected: 1 command with argv [cat] and input redirection to input.txt
*/
static int	test_input_redirection(void)
{
	char	*argv[] = {"cat", NULL};
	int		argc = 1;
	return (run_parser_test(3, "Input redirection", "cat < input.txt", argv, argc));
}

/*
** Test 4: Command with output redirection
** Input: "echo hello > output.txt"
** Expected: 1 command with argv [echo, hello] and output redirection
*/
static int	test_output_redirection(void)
{
	char	*argv[] = {"echo", "hello", NULL};
	int		argc = 2;
	return (run_parser_test(4, "Output redirection", "echo hello > output.txt", argv, argc));
}

/*
** Test 5: Multiple pipes
** Input: "ls | grep test | wc -l"
** Expected: 3 commands
*/
static int	test_multiple_pipes(void)
{
	char	*argv[] = {"ls", NULL};
	int		argc = 1;
	return (run_parser_test(5, "Multiple pipes", "ls | grep test | wc -l", argv, argc));
}

/*
** Test 6: Command with redirections and pipe
** Input: "cat < in.txt | grep test > out.txt"
** Expected: 2 commands with appropriate redirections
*/
static int	test_complex_pipe_redirections(void)
{
	char	*argv[] = {"cat", NULL};
	int		argc = 1;
	return (run_parser_test(6, "Complex pipe with redirections", 
		"cat < in.txt | grep test > out.txt", argv, argc));
}

/*
** Test 7: Quoted arguments
** Input: "echo \"hello world\""
** Expected: 1 command with argv [echo, "hello world"]
*/
static int	test_quoted_arguments(void)
{
	char	*argv[] = {"echo", "\"hello world\"", NULL};
	int		argc = 2;
	return (run_parser_test(7, "Quoted arguments", "echo \"hello world\"", argv, argc));
}

/*
** Test 8: Append redirection
** Input: "echo hello >> output.txt"
** Expected: 1 command with append redirection
*/
static int	test_append_redirection(void)
{
	char	*argv[] = {"echo", "hello", NULL};
	int		argc = 2;
	return (run_parser_test(8, "Append redirection", "echo hello >> output.txt", argv, argc));
}

/*
** Test 9: Heredoc
** Input: "cat << EOF"
** Expected: 1 command with heredoc redirection
*/
static int	test_heredoc(void)
{
	char	*argv[] = {"cat", NULL};
	int		argc = 1;
	return (run_parser_test(9, "Heredoc", "cat << EOF", argv, argc));
}

/*
** Test 10: Command with arguments and flags
** Input: "ls -la | grep -v total"
** Expected: 2 commands with their respective arguments
*/
static int	test_complex_arguments(void)
{
	char	*argv[] = {"ls", "-la", NULL};
	int		argc = 2;
	return (run_parser_test(10, "Complex arguments", "ls -la | grep -v total", argv, argc));
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
		NULL
	};
	return (tests);
}
