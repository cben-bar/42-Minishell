/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:34:51 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 04:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	write_option(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '\n')
				;
			else
			{
				write(1, &arg[i][j], 1);
			}
			j++;
		}
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
}

static void	write_vanilla(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
}

static int	is_option(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-1);
	if (arg[i++] != '-')
		return (-1);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (-1);
		i++;
	}
	return (1);
}

int	builtin_echo(char **arg, t_instance *instance)
{
	int	i;

	(void)instance;
	i = 1;
	while (arg[i] && is_option(arg[i]) == 1)
		i++;
	if (i > 1)
		write_option(&arg[i]);
	else
		write_vanilla(&arg[i]);
	if (i == 1)
		write(1, "\n", 1);
	return (0);
}
