/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:23:41 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 00:34:12 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_builtin	*init_built2(t_builtin *built)
{
	built->iter->name = ft_strdup("export");
	built->iter->fun = builtin_export;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("env");
	built->iter->fun = built_in_env;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("pwd");
	built->iter->fun = built_in_pwd;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("unset");
	built->iter->fun = builtin_unset;
	built->iter->next = NULL;
	built->iter = built->first;
	return (built);
}

t_builtin	*init_builtin(void)
{
	t_builtin	*built;

	built = malloc(sizeof(t_builtin));
	built->first = malloc(sizeof(t_btin));
	built->iter = built->first;
	built->iter->name = ft_strdup("cd");
	built->iter->fun = builtin_cd;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("exit");
	built->iter->fun = exit_builtin;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("echo");
	built->iter->fun = builtin_echo;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	return (init_built2(built));
}

static void	addpwd(t_instance	*instance)
{
	char	*pwd[3];

	pwd[0] = getcwd(NULL, 0);
	pwd[1] = ft_strjoin("PWD=", pwd[0]);
	pwd[2] = NULL;
	builtin_export(pwd, instance);
	free(pwd[0]);
	free(pwd[1]);
}

static void	add_(t_instance	*instance)
{
	char	*pwd[3];

	pwd[0] = ft_strdup("unset");
	pwd[1] = ft_strdup("_");
	pwd[2] = NULL;
	builtin_unset(pwd, instance);
	free(pwd[0]);
	free(pwd[1]);
	pwd[0] = ft_strdup("export");
	pwd[1] = ft_strjoin("_=", "/usr/bin/env");
	pwd[2] = NULL;
	builtin_export(pwd, instance);
	free(pwd[0]);
	free(pwd[1]);
}

t_instance	*init_minishell(char **envp, int ac, char **av)
{
	t_instance	*instance;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	instance = malloc(sizeof(t_instance));
	if (!instance)
		return (NULL);
	instance->builtin = init_builtin();
		instance->envp = init_envp(envp);
	addpwd(instance);
	addshlv(instance);
	add_(instance);
	return (instance);
}
