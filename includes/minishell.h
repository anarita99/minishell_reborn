/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:05:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/09 15:07:54 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libft
# include "libft.h"

// malloc, exit, getenv
# include <stdlib.h>

// write, access, read, close, fork
// getcwd, chdir, unlink, execve, dup/dup2
// pipe, isatty, ttyname, ttyslot
# include <unistd.h>

// printf, perror
# include <stdio.h>

// open
# include <fcntl.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// wait
# include <sys/wait.h>

// signal, sigaction, sigemptyset, sigaddset
// kill
# include <signal.h>

// stat
# include <sys/stat.h>

// opendir, readdir, closedir
# include <sys/types.h>
# include <dirent.h>

// strerror
# include <string.h>

// ioctl
# include <sys/ioctl.h>

// tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum
// tgetstr, tgoto, tputs
# include <termios.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIT_OUT,
	T_HEREDOC,
	T_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_token	*lexer(char *input);

#endif