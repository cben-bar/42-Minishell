/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:35:36 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:36:16 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirect(t_redir *redir, int *fdin, int *fdout)
{
	if (!redir)
		return (-1);
	if (redir->flag == HERE_DOC_FLAG)
		return (redir_hdoc(redir, fdin));
	else if (redir->flag == REDIR_IN_FLAG)
		return (redir_in(redir, fdin));
	else if (redir->flag == REDIR_OUT_ADD_FLAG)
		return (redir_out_append(redir, fdout));
	else if (redir->flag == REDIR_OUT_FLAG)
		return (redir_out(redir, fdout));
	return (0);
}

int	redirection(t_exec *exec)
{
	int	errcode;

	errcode = 0;
	if (exec->r_first == 0)
		return (0);
	exec->r_iter = exec->r_first;
	while (exec->r_iter != NULL)
	{
		errcode = redirect(exec->r_iter, &exec->fdin, &exec->fdout);
		if (redir_error(exec, errcode) == -1)
			return (-1);
		exec->r_iter = exec->r_iter->next;
	}
	exec->r_iter = exec->r_first;
	return (0);
}

int	redir_error(t_exec *cmd, int errcode)
{
	if (errcode == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->r_iter->redir, ft_strlen(cmd->r_iter->redir));
		write(2, ": No such file or directory\n", 29);
		g_status = 1;
		if (cmd->pid != 0)
			exit (1);
		return (-1);
	}
	return (1);
}
