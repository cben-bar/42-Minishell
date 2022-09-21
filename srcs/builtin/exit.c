/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:06:32 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 02:40:45 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_good_value(char *arg)
{
	int	i;

	i = 0;
	if ((arg[i] != '-' && arg[i] != '+'
			&& arg[i] <= '9' && arg[i] >= '0'))
		return (-1);
	i = 1;
	while (arg[i])
	{
		if (arg[i] > '9' || arg[i] < '0' || i >= 19)
			return (-1);
		i++;
	}
	return (0);
}

static int	check_ext_arg(char **arg)
{
	int	i;
	int	gud;

	i = 1;
	while (arg[i])
	{
		gud = check_good_value(arg[i]);
		if (gud == 0 && i > 1)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (-1);
		}
		else if (gud == -1)
		{
			write(2, "minishell: exit:", 17);
			write(2, arg[i], ft_strlen(arg[i]));
			write(2, ": numeric argument required\n", 29);
			return (-2);
		}
		i++;
	}
	return (0);
}

int	exit_builtin(char **arg, t_instance *instance)
{
	int	gud;

	(void)instance;
	write(2, "exit\n", 5);
	gud = check_ext_arg(arg);
	if (gud == -1)
		return (1);
	if (arg[1] != NULL)
		g_status = ft_atoi(arg[1]);
	else
		g_status = 0;
	free_instance(instance, 0);
	rl_clear_history();
	exit (g_status);
	return (0);
}
