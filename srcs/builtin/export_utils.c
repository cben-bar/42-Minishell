/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:13:29 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:39:23 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_in_set(char c)
{
	if (!((c >= '0' && c <= '9')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| c == '_'))
		return (0);
	return (1);
}

int	is_first_set(char c)
{
	if (!((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| c == '_'))
		return (0);
	return (1);
}

int	parse_export(char *varname)
{
	int	i;

	i = 0;
	while (varname[i])
	{
		if (!is_in_set(varname[i]) || !is_first_set(varname[0]))
		{
			write(2, "minishell: export: '", 21);
			write(2, varname, ft_strlen(varname));
			write(2, "': not a valid identifier\n", 27);
			free(varname);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*get_export(char *new)
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
