/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:06:29 by adores            #+#    #+#             */
/*   Updated: 2026/03/31 14:53:46 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_join(char *dir, char *cmd)
{
	char	*slash;
	char	*res;

	slash = ft_strjoin(dir, "/");
	if (!slash)
		return (NULL);
	res = ft_strjoin(slash, cmd);
	free(slash);
	return (res);
}

static char	*try_path(char *dir, char *cmd, bool *err)
{
	char	*path;

	path = path_join(dir, cmd);
	if (!path)
		return (*err = true, NULL);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*get_cmd_path(char *paths, char *cmd)
{
	int		i;
	char	*path;
	char	**splitpath;
	bool	err;

	i = 0;
	splitpath = ft_split(paths, ':');
	if (!splitpath)
		return (NULL);
	while (splitpath[i])
	{
		err = false;
		path = try_path(splitpath[i], cmd, &err);
		if (err)
			return (ft_freearray(splitpath), NULL);
		if (path)
			return (ft_freearray(splitpath), path);
		i++;
	}
	ft_freearray(splitpath);
	return (NULL);
}

char	*path_to_execute(char *cmd)
{
	struct stat	filedata;
	char		*path;
	char		*return_path;

	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &filedata) == -1)
			err_and_exit(cmd, "No such file or directory", 127, false);
		if (S_ISDIR(filedata.st_mode))
			err_and_exit(cmd, "Is a directory", 126, false);
		if (access(cmd, X_OK))
			err_and_exit(cmd, "Permission denied", 126, false);
		return_path = ft_strdup(cmd);
		return (return_path);
	}
	path = get_env_value(sh_s()->env_list, "PATH");
	if (!path)
		err_and_exit(cmd, "No such file or directory", 127, false);
	return_path = get_cmd_path(path, cmd);
	if (return_path == NULL)
		err_and_exit(cmd, "command not found", 127, false);
	return (return_path);
}
