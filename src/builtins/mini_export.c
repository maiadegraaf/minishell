/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:11:56 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/16 17:02:02 by fpolycar      ########   odam.nl         */
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

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void) simple_cmd;
	int	i;

	i = 0;
	variable_exist(tools, simple_cmd);
	// if (simple_cmd->str[1])
	// {
	// 		i = 0;
	// 		while(tools->envp[i])
	// 			i++;
	// 		tools->envp[i] = malloc(sizeof(char) * ft_strlen(simple_cmd->str[1]));
	// 		tools->envp[i] = simple_cmd->str[1];
	// 		tools->envp[i + 1] = NULL;
	// }
	return (EXIT_SUCCESS);
}
