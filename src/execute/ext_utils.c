/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:06:29 by adores            #+#    #+#             */
/*   Updated: 2026/02/12 16:53:11 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmd_path(char *paths, char *cmd)
{
	int		i;
	char	*add_path;
	char	*path;
	char	**splitpath;

	i = 0;
	splitpath = ft_split(paths, ':');
	if(!splitpath)
		return(NULL);
	while (splitpath[i])
	{
		add_path = ft_strjoin(splitpath[i], "/");
		path = ft_strjoin(add_path, cmd);
		free(add_path);
		if (access(path, X_OK) == 0)
		{
			free_arr(splitpath);
			return (path);
		}
		free(path);
		i++;
	}
	free_arr(splitpath);
	return (print_err(cmd, "command not found", false), NULL);
}

char	*path_to_execute(char *cmd)
{
	struct stat filedata;
	char	*path;
	char	*return_path;

	if(strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &filedata) == -1)
			error_exit(cmd, "No such file or directory", 127, false);
		if (S_ISDIR(filedata.st_mode))
			error_exit(cmd, "Is a directory", 126, false);
		if(access(cmd, X_OK))
			error_exit(cmd, "Permission denied", 126, false);
		return_path = ft_strdup(cmd);
		return (return_path);
	}
	path = get_env_value(sh_s()->env_list, "PATH");
	if(!path)
		error_exit(cmd, "No such file or directory", 127, false);
	return_path = get_cmd_path(path, cmd);
	if(return_path == NULL)
		error_exit(cmd, "No such file or directory", 127, false);
	return (return_path);
}
