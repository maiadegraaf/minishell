/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 14:35:54 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/14 17:02:24 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global.in_heredoc)
	{
		g_global.stop_heredoc = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
}
