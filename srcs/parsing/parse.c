/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:42:39 by cben-bar          #+#    #+#             */
/*   Updated: 2022/09/13 17:41:40 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*parse_2(t_control_parse *origin, char **env)
{
	t_control_parse	*replace;

	replace = init_control_parse();
	if (!replace)
		return (NULL);
	if (!dollar(origin, env))
		return (NULL);
	splitter(origin, replace, 2);
	cleaner(origin);
	flaggeur_redir(replace);
	cut_redir(replace);
	flaggeur_redir(replace);
	flaggeur_file_name(replace);
	re_flaggeur(replace);
	check_multi_chev(replace);
	if (!check_multi_node_chev(replace))
		return (NULL);
	if (!check_no_file_name(replace))
		return (NULL);
	supp_empty_node(replace);
	if (!quote_supp(replace))
		return (NULL);
	re_flaggeur(replace);
	return (replace);
}

t_control_parse	*parse(t_control_parse *parsing, size_t x, char **env)
{
	t_control_parse	*replace;

	replace = init_control_parse();
	if (!replace)
		return (NULL);
	if (x > 1)
	{
		while (parsing->iter->next)
		{
			parse_add_just_back(parsing, init_parse(ft_strdup("|"), 7));
			parsing->iter = parsing->iter->next;
			parsing->iter = parsing->iter->next;
		}
	}
	if (x == 1)
		parsing->first->flag = 5;
	splitter(parsing, replace, 1);
	replace = parse_2(replace, env);
	cleaner(parsing);
	if (replace == NULL)
		return (NULL);
	return (replace);
}
