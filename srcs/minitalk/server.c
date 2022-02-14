/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 10:49:07 by fpolycar      #+#    #+#                 */
/*   Updated: 2021/12/15 13:44:26 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	g_msg;

static void	handler_msg(int signum)
{
	g_msg.c += ((signum & 1) << (g_msg.size));
	g_msg.size++;
	if (g_msg.size == 8)
	{
		ft_putchar_fd(g_msg.c, 1);
		if (!g_msg.c)
			ft_putchar_fd('\n', 1);
		g_msg.c = 0;
		g_msg.size = 0;
	}
}

void	display_pid(void)
{
	int		pid;
	char	*str_pid;

	pid = getpid();
	str_pid = ft_itoa(pid);
	if (!str_pid)
	{
		ft_putendl_fd("Error at ft_itoa()", 1);
		return ;
	}
	ft_putstr_fd("PID: ", 1);
	ft_putendl_fd(str_pid, 1);
	free(str_pid);
}

int	main(void)
{
	g_msg.c = 0;
	g_msg.size = 0;
	display_pid();
	while (1)
	{
		signal(SIGUSR2, handler_msg);
		signal(SIGUSR1, handler_msg);
		pause();
	}
}
