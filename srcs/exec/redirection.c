/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:02:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/24 03:46:57 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_in(t_redir *redir, int *fd)
{
	int	tmp;

	tmp = *fd;
	if (access(redir->redir, F_OK | R_OK) == -1)
	{
		close (tmp);
		return (-1);
	}
	*fd = open(redir->redir, O_RDONLY);
	if (*fd == -1)
	{
		close (tmp);
		return (-2);
	}
	if (tmp >= 3)
		close (tmp);
	return (0);
}

int	redir_out_append(t_redir *redir, int *fd)
{
	int	tmp;

	tmp = *fd;
	*fd = open(redir->redir, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (*fd == -1)
	{
		*fd = tmp;
		return (1);
	}
	if (tmp >= 3)
		close (tmp);
	return (0);
}

int	redir_out(t_redir *redir, int *fd)
{
	int	tmp;

	tmp = *fd;
	*fd = open(redir->redir, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd == -1)
	{
		*fd = tmp;
		return (1);
	}
	if (tmp >= 3)
		close (tmp);
	return (0);
}

int	redir_hdoc(t_redir *redir, int *fd)
{
	int	tmp;

	tmp = *fd;
	if (here_doc(redir, fd) == -1)
	{
		close (tmp);
		return (-3);
	}
	if (tmp >= 3)
		close (tmp);
	return (0);
}
