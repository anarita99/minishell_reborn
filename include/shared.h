/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:33:10 by adores            #+#    #+#             */
/*   Updated: 2026/02/12 17:38:55 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <stdbool.h>
# include <linux/limits.h>
// libft
# include "../libft/libft.h"

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