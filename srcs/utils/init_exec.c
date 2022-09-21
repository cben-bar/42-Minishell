/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:18:59 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/09 14:25:54 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_exec	*init_exe(void)
{
	t_exec	*exe;
	int		i;

	i = 0;
	exe = (t_exec *)malloc(sizeof(t_exec));
	exe->r_first = NULL;
	exe->r_iter = NULL;
	exe->next = NULL;
	exe->prev = NULL;
	exe->is_builtin = false;
	exe->pid = 0;
	exe->fdin = -1;
	exe->fdout = -1;
	while (i < 100)
	{
		exe->cmd[i] = NULL;
		exe->is_append[i] = '\0';
		i++;
	}
	return (exe);
}

t_control_exec	*init_exe_list(void)
{
	t_control_exec	*exe;

	exe = malloc(sizeof(t_control_exec));
	exe->first = NULL;
	exe->iter = NULL;
	return (exe);
}
