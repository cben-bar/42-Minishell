/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:39:10 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:39:11 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

static int	sort_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0x00 && (s1[i] == s2[i]))
		i++;
	return (*s1 - *s2);
}

char	**sort_ascii(char **envp)
{
	int		i;
	char	**sorted;

	i = 1;
	sorted = init_envp(envp);
	if (!sorted)
		return (NULL);
	while (sorted[i])
	{
		if (sort_strcmp(sorted[i - 1], sorted[i]) > 0)
		{
			ft_swap(&sorted[i], &sorted[i - 1]);
			i = 0;
		}
		i++;
	}
	return (sorted);
}
