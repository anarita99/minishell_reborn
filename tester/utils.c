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

void	print_passed()
{
	printf("✅ PASSED\n");
}

void	print_failed()
{
	printf("❌ FAILED\n");
}

void	print_passed_count(int count, int max)
{
	if (count == max)
		printf("✅");
	else
		printf("❌");
	printf(" PASSED %i/%i\n", count, max);
}
