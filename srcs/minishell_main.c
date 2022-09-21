/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:20:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/13 02:46:42 by acarle-m         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

static int	if_line(t_instance *instance)
{
	t_control_parse	*parse;
	t_control_exec	*exec;
	int				nb_pipe;

	nb_pipe = 0;
	if (instance->line[0] != 13)
		add_history(instance->line);
	parse = parsing(instance->line, instance->envp);
	if (control_parse(parse) == -1)
		return (-1);
	parse->iter = parse->first;
	nb_pipe = pipe_counter(parse);
	exec = structy(parse, nb_pipe, instance->envp);
	parse->iter = parse->first;
	cleaner(parse);
	if (!exec)
		return (-1);
	chose_exec(exec, instance);
	exec_cleaner(exec);
	instance->builtin->iter = instance->builtin->first;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_instance	*instance;

	instance = init_minishell(envp, ac, av);
	if (!instance)
		return (-1);
	uncannon(&instance->shell);
	while (1)
	{
		instance->line = readline("minishell $>");
		if (!instance->line)
			break ;
		else if (instance->line || instance->line[0] != 13)
			if_line(instance);
		if (instance->line)
			free(instance->line);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	restore(&instance->shell.saved);
	free_instance(instance, 1);
	exit (EXIT_SUCCESS);
	return (1);
}
