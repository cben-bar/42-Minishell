/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:17:02 by cben-bar          #+#    #+#             */
/*   Updated: 2022/09/15 15:25:19 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var	*node_env(char *varname, t_var *var)
{
	while (var)
	{
		if (ft_strcmp(varname, var->varname) == 0)
			break ;
		var = var->next;
	}
	return (var);
}

t_bool	in_charset(char c, int index)
{
	if (index == 0)
	{
		if (!is_first_set(c) && c != '?')
			return (true);
	}
	else
	{
		if (!is_in_set(c) && c != '?')
			return (true);
	}
	return (false);
}

char	*find_name(char *s, size_t dellen, size_t i, size_t j)
{
	char	*varname;
	int		q;

	varname = malloc(sizeof(char) * dellen);
	q = 0;
	while (s[i] && j == 0)
	{
		q = tote(s[i], q);
		if (q != 1 && s[i] == '$')
		{
			i++;
			while ((j < dellen - 1) && !in_charset(s[i], j))
			{
				varname[j] = s[i];
				j++;
				i++;
			}
			varname[j] = '\0';
		}
		i++;
	}
	return (varname);
}

int	search_value(char *varname, t_var *var)
{
	t_var	*start;

	start = var;
	if (ft_strcmp(varname, "?") == 0)
		return (2);
	while (var)
	{
		if (ft_strcmp(varname, var->varname) == 0)
			return (1);
		var = var->next;
	}
	var = start;
	return (0);
}

size_t	cpy_value_2(char *dst, char *value, size_t i)
{
	while (value[i])
	{
		dst[i] = value[i];
		i++;
	}
	return (i);
}
