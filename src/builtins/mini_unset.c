/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_unset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:13:32 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/23 12:45:43 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int variable_exist_del(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;
	int j;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], simple_cmd->str[1], equal_sign(tools->envp[i])) == 0)
		{
			j = 0;
			while (tools->envp[i + j])
			{
				tools->envp[i + j] = tools->envp[i + j + 1];
				j++;
			}
			tools->envp[i + j] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	mini_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int exist;

	if (!simple_cmd->str[1])
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
	if (equal_sign(simple_cmd->str[1]) != 0)
		ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
	else
		exist = variable_exist_del(tools, simple_cmd);
	return (EXIT_SUCCESS);
}
