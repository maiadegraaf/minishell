/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 12:09:05 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/18 14:02:43 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int		i;

	(void) simple_cmd;
	i = 0;
	while (tools->envp[i])
	{
		ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
