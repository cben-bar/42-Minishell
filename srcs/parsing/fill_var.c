/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:45:49 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:49:46 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var	*fill_var(t_var *var, char **envp)
{
	size_t	i;
	t_var	*new;
	t_var	*first;

	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	while (envp[i])
	{
		if (i == 0)
		{
			var = ft_lstnew(envp[i]);
			first = var;
		}
		else
		{
			new = ft_lstnew(envp[i]);
			var->next = new;
			var = new;
		}
		i++;
	}
	var->next = 0;
	dispatch_var(first);
	return (first);
}
