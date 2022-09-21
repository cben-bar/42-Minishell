/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:22:29 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:22:29 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_free(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return ;
	while (exec->cmd[i] != NULL)
	{
		free(exec->cmd[i]);
		i++;
	}
	r_free(exec->r_iter, exec->r_first);
	close(exec->fdin);
	close(exec->fdout);
	free(exec);
}

void	exec_cleaner(t_control_exec *exec)
{
	if (!exec)
		return ;
	exec->iter = exec->first;
	while (exec->first != NULL)
	{
		exec->iter = exec->first->next;
		exec_free(exec->first);
		exec->first = exec->iter;
	}
	free(exec);
}

int	control_parse(t_control_parse *truct)
{
	if (!truct)
		return (-1);
	if (!truct->first)
	{
		free(truct);
		return (-1);
	}
	return (0);
}

int	test_free(t_control_exec *exec, int nb_pipe)
{
	if (!exec)
		return (-1);
	exec->first = init_exe();
	exec->iter = exec->first;
	if (!exec->first)
	{
		free (exec);
		return (-1);
	}
	while (nb_pipe != 0)
	{
		if (exec_add_back(exec, init_exe()) == -1)
		{
			exec_cleaner(exec);
			return (-1);
		}
		nb_pipe--;
	}
	exec->iter = exec->first;
	return (0);
}

int	free_instance(t_instance *instance, int i)
{
	int		j;
	t_btin	*tmp;

	j = 0;
	while (instance->envp[j])
		free(instance->envp[j++]);
	free(instance->envp);
	tmp = instance->builtin->first;
	while (tmp != NULL)
	{
		instance->builtin->first = instance->builtin->first->next;
		free(tmp->name);
		free(tmp);
		tmp = instance->builtin->first;
	}
	free(instance->builtin);
	if (instance->line)
		free(instance->line);
	free(instance);
	return (i);
}
