/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:11:56 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/18 10:43:07 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int variable_exist(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], simple_cmd->str[1], equal_sign(tools->envp[i])) == 0)
		{
			tools->envp[i] = simple_cmd->str[1];
			return (1);
		}
		i++;
	}
	return (0);
}

int check_parameter(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		ft_putendl_fd("export: not an identifier", STDERR_FILENO);
		return (1);
	}
	if (str[0] == '=')
	{
		ft_putendl_fd("export: bad assignment", STDERR_FILENO);
		return (2);
	}
	return (0);
}

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	if (!simple_cmd->str[1])
		mini_env(tools, simple_cmd);
	else 
	{
		if (check_parameter(simple_cmd->str[1]) == 0)
		{
			if (variable_exist(tools, simple_cmd) == 0)
			{
				if (simple_cmd->str[1])
				{
						i = 0;
						while(tools->envp[i])
							i++;
						tools->envp[i] = tools->envp[i - 1];
						tools->envp[i - 1] = simple_cmd->str[1];
						tools->envp[i + 1] = NULL;
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}
