/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:15 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:15 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_one_builtin(t_exec *cmd, t_instance *instance)
{
	cmd->pid = 0;
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
	while (instance->builtin->iter->next
		&& ft_strncmp(cmd->cmd[0], instance->builtin->iter->name,
			ft_strlen(instance->builtin->iter->name)) != 0)
		instance->builtin->iter = instance->builtin->iter->next;
	g_status = (*instance->builtin->iter->fun)(cmd->cmd, instance);
	return (g_status);
}

static int	exec_one_cmd(t_exec *cmd, t_instance *instance)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, sig_int_child_handler);
		signal(SIGQUIT, sig_quit_handler);
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
		execve(cmd->cmd[0], cmd->cmd, instance->envp);
		exec_free(cmd);
		exit (free_instance(instance, errno));
	}
	set_g_status(pid);
	return (0);
}

static int	execution_solo(t_exec *cmd, t_instance *instance)
{
	int	save[2];
	int	ret;

	save[0] = dup(0);
	save[1] = dup(1);
	if (redirection(cmd) == -1)
		return (-1);
	if (cmd->is_builtin == true)
		ret = exec_one_builtin(cmd, instance);
	else
		ret = exec_one_cmd(cmd, instance);
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(save[0]);
	close(save[1]);
	return (ret);
}

static int	execution_pipe(t_control_exec *exes, t_instance *instance)
{
	int	save[2];

	fd_save(save);
	exes->iter = exes->first;
	while (exes->iter != NULL)
	{
		if (redirection(exes->iter) == -1)
			return (-1);
		exes->iter = exes->iter->next;
	}
	exes->iter = exes->first;
	while (exes->iter->next != NULL)
	{
		forklift(exes, instance);
		exes->iter = exes->iter->next;
	}
	dup2(save[1], 1);
	last_pipe(exes->iter, instance);
	fd_retore(save);
	wait_all(exes);
	exes->iter = exes->first;
	return (0);
}

int	chose_exec(t_control_exec *exes, t_instance *instance)
{
	int	ret;

	ret = 0;
	rerestore(&instance->shell);
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler_exec);
	if (ft_strncmp(exes->first->cmd[0], "./minishell", 12) == 0)
	{
		signal(SIGINT, null_signal);
		signal(SIGQUIT, null_signal);
	}
	if (!exes->first)
		return (-1);
	if (exes->first->next == NULL)
		ret = execution_solo(exes->first, instance);
	else
		ret = execution_pipe(exes, instance);
	exes->iter = exes->first;
	reuncannon(&instance->shell);
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	return (ret);
}
