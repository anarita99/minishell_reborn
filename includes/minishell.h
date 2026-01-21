/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:05:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/01/16 16:06:05 by leramos-         ###   ########.fr       */
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

t_token	*lexer(char *input);

#endif