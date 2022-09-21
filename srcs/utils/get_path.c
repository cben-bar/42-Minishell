/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:22:11 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:22:11 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*cmd_bad_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 21);
	}
	else if (access(cmd, X_OK) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 21);
	}
	return (cmd);
}

static char	*cmd_or_directory(char *cmd, int a)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, "minishell: ", 12);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": is a directory\n", 18);
		if (a == 1)
			return (NULL);
	}
	return (cmd);
}

char	*get_path(char *cmd, char **envp, size_t j)
{
	char	**paths;
	char	*path;

	j = 0;
	if (cmd_or_directory(cmd, 1) == NULL)
		return (cmd);
	while (envp[j] && ft_strnstr(envp[j], "PATH=", 5) == 0)
		j++;
	if (envp[j] == NULL)
		return (cmd_bad_access(cmd));
	paths = exec_split(envp[j] + 5, ':');
	j = -1;
	while (paths[++j] != NULL)
	{
		path = ft_strfreejoin(ft_strjoin(paths[j], "/"), cmd);
		if (access(path, F_OK) == 0)
		{
			cmd_free(paths);
			free(cmd);
			return (cmd_or_directory(path, 0));
		}
		free(path);
	}
	cmd_free(paths);
	return (cmd_bad_access(cmd));
}
