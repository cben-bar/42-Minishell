/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:52:18 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/15 15:02:31 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	findaddlen(char *s, size_t dellen, t_var *var)
{
	char	*varname;
	size_t	addlen;
	t_var	*start;
	size_t	i;
	size_t	j;

	start = var;
	addlen = 0;
	i = 0;
	j = 0;
	varname = find_name(s, dellen, i, j);
	addlen = ft_find_value(varname, var);
	free(varname);
	var = start;
	return (addlen);
}

size_t	finddellen(char *s, size_t i)
{
	int	n;
	int	q;
	int	del;

	del = 0;
	while (s[i])
	{
		n = i + 1;
		q = tote(s[i], q);
		if (q != 1 && s[i] == '$')
		{
			del = 1;
			while (is_first_set(s[n]) || s[n] == '?')
			{
				n++;
				del++;
			}
			if ((s[n] >= '0' && s[n] <= '9'))
				return (del + 1);
			return (del);
		}
		i++;
	}
	return (del);
}

int	ft_alloc(t_parse *node, t_var *var)
{
	size_t	delen;
	size_t	addlen;
	char	*s;
	size_t	i;

	i = 0;
	delen = finddellen(node->elem, i);
	if (delen == 0)
		return (true);
	addlen = findaddlen(node->elem, delen, var);
	s = malloc(sizeof(char) * (ft_strlen(node->elem) + addlen - delen + 1));
	if (!s)
		return (false);
	sub_it(s, node, var, delen);
	free(node->elem);
	node->elem = s;
	return (true);
}

t_bool	there_is_doll(char *s)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	while (s[i])
	{
		q = tote(s[i], q);
		if ((q == 0 || q == 2) && s[i] == '$'
			&& (is_in_set(s[i + 1]) || s[i + 1] == '?'))
			return (true);
		i++;
	}
	return (false);
}

int	dollar(t_control_parse *parsing, char **env)
{
	t_var	*var;

	var = set_var(env);
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (there_is_doll(parsing->iter->elem))
		{
			if (!ft_alloc(parsing->iter, var))
				return (false);
		}
		else
			parsing->iter = parsing->iter->next;
	}
	var_clear(var);
	return (true);
}
