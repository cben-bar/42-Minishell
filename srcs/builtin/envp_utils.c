/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:39 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:39 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_envp(char **envp)
{
	char	**env_ret;
	size_t	size;
	int		i;

	size = ft_size(envp);
	env_ret = malloc((size + 1) * sizeof(char *));
	if (!env_ret)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_ret[i] = ft_strdup(envp[i]);
		i++;
	}
	env_ret[size] = NULL;
	return (env_ret);
}

char	**add_envp(char **envp, char *new)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_size(envp) + 2));
	if (new_envp == NULL)
		return (envp);
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	new_envp[i] = ft_strdup(new);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

char	*get_varname(char *new)
{
	int		i;
	char	*ret;

	i = 0;
	while (new[i])
	{
		if (new[i + 1] == '=')
			break ;
		i++;
	}
	if (new[i + 1] != '=')
		return (NULL);
	ret = (char *)malloc(i + 2);
	if (!ret)
		return (NULL);
	ret[i + 1] = 0;
	while (i >= 0)
	{
		ret[i] = new[i];
		i--;
	}
	return (ret);
}

char	**del_envp(char **envp, int index)
{
	char	**new_envp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new_envp = malloc(sizeof(char *) * (ft_size(envp) + 1));
	if (new_envp == NULL)
		return (envp);
	while (envp[i] != NULL)
	{
		if (i != index)
		{
			new_envp[k] = ft_strdup(envp[i]);
			k++;
		}
		free(envp[i]);
		i++;
	}
	free(envp);
	new_envp[k] = NULL;
	return (new_envp);
}

void	addshlv(t_instance *instance)
{
	int		i;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return ;
	tmp[2] = NULL;
	i = -1;
	while (instance->envp[++i])
		if (ft_strnstr(instance->envp[i], "SHLVL=", 6) != 0)
			break ;
	if (instance->envp[i] == NULL)
	{
		tmp[0] = ft_strdup("export");
		tmp[1] = ft_strdup("SHLVL=1");
	}
	else
	{
		tmp[0] = ft_itoa(ft_atoi(instance->envp[i] + 6) + 1);
		tmp[1] = ft_strjoin("SHLVL=", tmp[0]);
	}
	builtin_export(tmp, instance);
	cmd_free(tmp);
}
