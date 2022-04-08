/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 14:35:54 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/08 17:46:30 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("minishell$   \n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
