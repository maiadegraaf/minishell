/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_cd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 15:17:04 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/18 10:47:00 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "builtins.h"

char *find_path_ret(char *str, t_tools *tools)
{
	int i;

	i = 0;
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], str, ft_strlen(str)))
			return (ft_substr(tools->envp[i], ft_strlen(str), ft_strlen(tools->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	ret;

	if (!simple_cmd->str[1])
	{
		ret = chdir(find_path_ret("HOME=", tools));
		if (ret != 0)
		{
			ft_putendl_fd("HOME not set", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(simple_cmd->str[1], "-", 1) == 0)
	{
		ret = chdir(find_path_ret("OLDPWD=", tools));
		if (ret != 0)
		{
			ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		ret = chdir(simple_cmd->str[1]);
		if (ret != 0)
		{
			ft_putendl_fd("Path do not exist", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	change_path(tools);
	return (EXIT_SUCCESS);
}
