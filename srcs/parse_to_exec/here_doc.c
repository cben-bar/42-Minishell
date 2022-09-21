/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:37:24 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/21 04:37:25 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	utils_hdoc(t_redir *redir, int *pipefd)
{
	char	*line;
	size_t	tmp;

	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, sig_quit_handler);
	close(pipefd[0]);
	tmp = ft_strlen(redir->redir);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, redir->redir, tmp) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	if (line)
		free(line);
	close(pipefd[1]);
	close(pipefd[0]);
	exit (0);
}

int	here_doc(t_redir *redir, int *fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		utils_hdoc(redir, pipefd);
	else
	{
		close(pipefd[1]);
		*fd = pipefd[0];
		waitpid(pid, NULL, 0);
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
