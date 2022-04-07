/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:10:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/06 10:33:43 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <signal.h>
//probably have to add some frees in here.

int	mini_exit(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void) simple_cmd;
	printf("%d\n", tools->end_pid);
	ft_putstr_fd("exit", STDERR_FILENO);
	
	tools->end = true;
	kill(0, SIGINT);
	// exit (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
