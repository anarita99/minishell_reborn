/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:22:15 by adores            #+#    #+#             */
/*   Updated: 2026/03/26 16:48:21 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

static void	handler_signals(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sh_s()->exit_status = 130;
}

void	child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	setup_signals(void)
{
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_wait_status(int w_status)
{
	int	sig;

	if (WIFSIGNALED(w_status))
	{
		sig = WTERMSIG(w_status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 1);
		else if (sig == SIGINT)
			write(1, "\n", 1);
		sh_s()->exit_status = sig + 128;
	}
	else if (WIFEXITED(w_status))
		sh_s()->exit_status = WEXITSTATUS(w_status);
}
