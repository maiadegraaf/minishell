/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 14:35:54 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/13 13:04:58 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("%sminishell%s$%s", CYAN_BOLD, BLUE, RESET_COLOR);
	rl_redisplay();
	(void) sig;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
}
