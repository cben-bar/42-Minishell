/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdrestore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:38:58 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:38:58 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fd_retore(int save[2])
{
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(save[1]);
	close(save[0]);
	return (0);
}

int	fd_save(int save[2])
{
	save[0] = dup(0);
	save[1] = dup(1);
	return (0);
}
