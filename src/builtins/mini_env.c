/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 12:09:05 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/16 10:07:26 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;
	(void) simple_cmd;

	i = 0;
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
		{
			ft_putstr_fd("PWD=", STDOUT_FILENO);
			ft_putendl_fd(tools->pwd, STDOUT_FILENO);
		}
		else if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7))
		{
			ft_putstr_fd("OLDPWD=", STDOUT_FILENO);
			ft_putendl_fd(tools->old_pwd, STDOUT_FILENO);
		}
		else
			ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
		i++;
	}
	return (1);
}
