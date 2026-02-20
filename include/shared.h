/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:33:10 by adores            #+#    #+#             */
/*   Updated: 2026/02/20 14:32:44 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

// Bool and NULL
# include <stdbool.h>
# include <limits.h>

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
# include <errno.h>

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

#endif