/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:31 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:31 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse_unset(char *varname)
{
	int	i;

	i = 0;
	while (varname[i])
	{
		if (!is_in_set(varname[i]) || !is_first_set(varname[0]))
		{
			write(2, "minishell: unset: '", 20);
			write(2, varname, ft_strlen(varname));
			write(2, "': not a valid identifier\n", 27);
			free(varname);
			return (-1);
		}
		i++;
	}
	return (0);
}

static char	**loop(char **envp, char *arg)
{
	int		j;
	char	*varname;

	j = 0;
	if (parse_unset(arg))
		return (envp);
	while (envp[j] != NULL)
	{
		varname = get_export(envp[j]);
		if (ft_strncmp(varname, arg, (ft_strlen(arg) + 1)) == 0)
		{
			envp = del_envp(envp, j);
			free(varname);
			return (envp);
		}
		free(varname);
		j++;
	}
	return (envp);
}

int	builtin_unset(char **arg, t_instance *instance)
{
	int	i;

	i = 1;
	while (arg[i] != NULL)
	{
		instance->envp = loop(instance->envp, arg[i]);
		i++;
	}
	return (0);
}
