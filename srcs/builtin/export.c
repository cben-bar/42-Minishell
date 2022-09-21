/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:35 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:35 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_export(char *arg)
{
	write(2, "minishell: ", 12);
	write(2, "export: '", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

int	name_len(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '=')
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static int	printf_env(t_instance *instance)
{
	int		i;
	int		j;
	char	**sorted_envp;

	i = -1;
	if (instance->envp == NULL)
		return (-1);
	sorted_envp = sort_ascii(instance->envp);
	while (sorted_envp[++i])
	{
		j = name_len(sorted_envp[i]);
		write(1, "declare -x ", 11);
		if (j != 0)
		{
			write(1, sorted_envp[i], ++j);
			write(1, "\"", 1);
			write(1, &sorted_envp[i][j], ft_strlen(sorted_envp[i]) - j);
			write(1, "\"", 1);
		}
		else
			write(1, sorted_envp[i], ft_strlen(sorted_envp[i]));
		write(1, "\n", 1);
	}
	cmd_free(sorted_envp);
	return (0);
}

static int	is_envp(char *arg, char **envp)
{
	int		i;
	char	*varname;
	size_t	len;

	i = 0;
	if (arg[0] == '=')
		return (-3);
	varname = get_export(arg);
	if (varname == NULL)
		return (-1);
	if (parse_export(varname) == -1)
		return (-4);
	len = ft_strlen(varname);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], varname, len) == 0)
		{
			free(varname);
			return (i);
		}
		i++;
	}
	free(varname);
	return (-2);
}

int	builtin_export(char **arg, t_instance *instance)
{
	int		i;
	int		j;

	i = 1;
	if (arg[i] == NULL)
		return (printf_env(instance));
	while (arg[i] != NULL)
	{
		j = is_envp(arg[i], instance->envp);
		if (j == -2)
			instance->envp = add_envp(instance->envp, arg[i++]);
		else if (j == -3)
			return (error_export(arg[i]));
		else if (j == -1)
			return (-1);
		else if (j == -4)
			i++;
		else
		{
			if (instance->envp[j])
				free(instance->envp[j]);
			instance->envp[j] = ft_strdup(arg[i++]);
		}
	}
	return (0);
}
