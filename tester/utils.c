/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/12 15:24:28 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	print_test_info(int n, char *name, char *input)
{
	printf("Test %i: %s\n", n, name);
	printf("- Input: \"%s\"\n", input);
}

static void	print_passed()
{
	printf("- Result: PASSED ✅\n");
}

static void	print_failed()
{
	printf("- Result: KO ❌\n");
}

static void	print_passed_count(int count, int max)
{
	if (count == max)
		printf("✅ PASSED ");
	else
		printf("❌ KO ");
	printf("%i/%i\n", count, max);
}

static int	get_test_count(int (**tests)(void))
{
	int	count;

	count = 0;
	while (tests[count] != NULL)
		count++;
	return (count);
}

void	run_tests(char *module_name, int (**tests)(void))
{
	int	test_count;
	int success_count;
	int	i;

	printf("════════════════════ %s TESTS ════════════════════\n", module_name);
	printf("\n");
	
	test_count = get_test_count(tests);
	success_count = 0;
	i = 0;
	while (i < test_count)
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
	print_passed_count(success_count, test_count);
	printf("\n");
}
