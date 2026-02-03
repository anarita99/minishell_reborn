/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:06:29 by adores            #+#    #+#             */
/*   Updated: 2026/02/03 18:06:55 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

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
			free_str_array(splitpath);
			return (path);
		}
		free(path);
		i++;
	}
	free_str_array(splitpath);
	return (print_err(cmd, "command not found", false), NULL);
}

char	*is_executable(char *cmd)
{
	struct stat filedata;
	char	*path;
	char	*return_path;

	if(strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &filedata) == -1)
			return (print_err(cmd, "No such file or directory", false), call_sh_struct()->last_exit_status = 127, NULL);
		if (S_ISDIR(filedata.st_mode))
			return (print_err(cmd, "Is a directory", false), call_sh_struct()->last_exit_status = 126, NULL);
		if(access(cmd, X_OK))
			return (print_err(cmd, "Permission denied", false), call_sh_struct()->last_exit_status = 126, NULL);
		return_path = cmd;
		return (return_path);
	}
	path = get_env_value(call_sh_struct()->env_list, "PATH");
	if(!path)
		return (print_err(cmd, "No such file or directory", false), call_sh_struct()->last_exit_status = 127, NULL);
	return_path = get_cmd_path(path, cmd);
	if(return_path == NULL)
		return(print_err(cmd, "No such file or directory", false), call_sh_struct()->last_exit_status = 127, NULL);
	return (return_path);
}
