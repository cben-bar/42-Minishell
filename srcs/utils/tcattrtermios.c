/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcattrtermios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:08:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/09/13 19:08:56 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	restore(struct termios *saved)
{
	tcsetattr(STDIN_FILENO, TCSANOW, saved);
}

void	uncannon(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->saved);
	tcgetattr(STDIN_FILENO, &shell->attributes);
	shell->attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->attributes);
}

void	rerestore(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->saved);
}

void	reuncannon(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->attributes);
}
