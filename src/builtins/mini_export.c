/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:07:21 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/30 14:53:22 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	variable_exist(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i],
				simple_cmd->str[1], equal_sign(tools->envp[i])) == 0)
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strdup(simple_cmd->str[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

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

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (str[0] == '\'' && str[ft_strlen(str)] == '\''
			&& str[0] == '\"' && str[ft_strlen(str)] == '\"')
			ft_strtrim(str, "\'\"");
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;

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
					tmp = add_var(tools->envp, simple_cmd->str[1]);
					free_arr(tools->envp);
					tools->envp = tmp;
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}
