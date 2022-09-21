/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:36:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:37:14 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*create_redir(int flag, char *redir)
{
	t_redir	*stct;

	stct = (t_redir *)malloc(sizeof(t_redir));
	stct->flag = flag;
	stct->redir = redir;
	stct->next = NULL;
	return (stct);
}

int	redir_last(t_exec *exec)
{
	if (!exec->r_first)
		return (-1);
	exec->r_iter = exec->r_first;
	while (exec->r_iter->next)
		exec->r_iter = exec->r_iter->next;
	return (1);
}

int	r_add_back(t_exec *exec, t_redir *redir)
{
	if (redir == NULL)
		return (-1);
	if (exec->r_first == NULL)
		exec->r_first = redir;
	else
	{
		if (!redir_last(exec))
			return (-1);
		exec->r_iter->next = redir;
	}
	exec->r_iter = exec->r_first;
	return (0);
}

void	r_free(t_redir *redir, t_redir *redir_f)
{
	if (!redir)
		return ;
	redir = redir_f;
	while (redir_f != NULL)
	{
		redir = redir_f->next;
		free(redir_f);
		redir_f = redir;
	}
}
