/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:10:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/12 13:37:11 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <signal.h>
//probably have to add some frees in here.

int	mini_exit(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int		status;

	status = tools->pid[tools->pipes];
	ft_putendl_fd("exit", STDERR_FILENO);
	if (simple_cmd->str[1] != NULL)
		status = ft_atoi(simple_cmd->str[1]);
	free_arr(simple_cmd->str);
	free_arr(tools->envp);
	exit(status);
	return (EXIT_SUCCESS);
}
