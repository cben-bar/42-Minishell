/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:04 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:04 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execuction(t_exec *cmd, t_instance *instance)
{
	int	ret;

	ret = 0;
	if (cmd->fdin != -1)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != -1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	if (cmd->is_builtin == true)
	{
		while (instance->builtin->iter->next
			&& ft_strcmp(cmd->cmd[0], instance->builtin->iter->name) != 0)
			instance->builtin->iter = instance->builtin->iter->next;
		exit ((*instance->builtin->iter->fun)(cmd->cmd, instance));
	}
	else
		ret = execve(cmd->cmd[0], cmd->cmd, instance->envp);
	exit (ret);
}

int	forklift(t_control_exec *exes, t_instance *instance)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	exes->iter->pid = fork();
	if (exes->iter->pid == -1)
		return (-1);
	if (exes->iter->pid == 0)
	{
		signal(SIGINT, sig_int_child_handler);
		signal(SIGQUIT, sig_quit_handler);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execuction(exes->iter, instance);
		exec_cleaner(exes);
		exit (free_instance(instance, errno));
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	last_pipe(t_exec *cmd, t_instance *instance)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (-1);
	if (cmd->pid == 0)
	{
		signal(SIGINT, sig_int_child_handler);
		signal(SIGQUIT, sig_quit_handler);
		execuction(cmd, instance);
		exec_free(cmd);
		exit (free_instance(instance, errno));
	}
	return (0);
}
