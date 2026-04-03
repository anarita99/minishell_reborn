/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:19:08 by adores            #+#    #+#             */
/*   Updated: 2026/03/30 16:19:24 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_eof_warning(char *del)
{
	ft_putstr_fd("minishell: warning: here-document delimited by \
end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putendl_fd("')", 2);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	sh_s()->exit_status = 700;
	close(STDIN_FILENO);
}
