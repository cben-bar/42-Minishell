/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:24:32 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/14 22:55:07 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_exec_error(void)
{
	int	tmp;

	tmp = WTERMSIG(g_status);
	if (tmp == SIGSEGV)
		write(2, "Segmentation fault\n", 19);
	else if (tmp == SIGBUS)
		write(2, "Bus error\n", 10);
	else if (tmp == SIGABRT)
		write(2, "Aborted\n", 8);
	else if (tmp == SIGFPE)
		write(2, "Floating point exception\n", 25);
	else if (tmp == SIGINT)
		g_status = 130;
	else if (tmp == SIGQUIT)
		g_status = 131;
}

int	set_g_status(int pid)
{
	waitpid(pid, &g_status, 0);
	if (WIFSIGNALED(g_status))
		get_exec_error();
	else if (WIFEXITED(g_status) && g_status != 127)
		g_status = WEXITSTATUS(g_status);
	if (g_status == EACCES)
		g_status = 126;
	else if (g_status == ENOENT)
		g_status = 127;
	return (1);
}

void	wait_all(t_control_exec *exes)
{
	exes->iter = exes->first;
	while (exes->iter && set_g_status(exes->iter->pid))
		exes->iter = exes->iter->next;
	exes->iter = exes->first;
}
