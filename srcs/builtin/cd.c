/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:44 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/15 15:14:06 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ret_pwd_arg(void)
{
	char	**arg;
	char	*tmp;

	arg = malloc(sizeof(char *) * 3);
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup("export");
	if (!arg[0])
		return (NULL);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	arg[1] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!arg[1])
		return (NULL);
	arg[2] = NULL;
	return (arg);
}

static char	**ret_old_pwd(void)
{
	char	**arg;
	char	*tmp;

	arg = malloc(sizeof(char *) * 3);
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup("export");
	if (!arg[0])
		return (NULL);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	arg[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	if (!arg[1])
		return (NULL);
	arg[2] = NULL;
	return (arg);
}

static void	free_oira(char **path)
{
	if (path)
	{
		if (path[0])
			free(path[0]);
		if (path[1])
			free(path[1]);
		free(path);
	}
}

int	builtin_cd(char **arg, t_instance *instance)
{
	char	**path;

	if (arg[1] == NULL)
		return (0);
	path = ret_old_pwd();
	if (!path)
		return (-1);
	builtin_export(path, instance);
	if (chdir(arg[1]) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, arg[0], ft_strlen(arg[0]));
		write(2, ": ", 2);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": No such file or directory\n", 29);
		free_oira(path);
		return (-1);
	}
	free_oira(path);
	path = ret_pwd_arg();
	if (!path)
		return (-1);
	builtin_export(path, instance);
	free_oira(path);
	return (0);
}
