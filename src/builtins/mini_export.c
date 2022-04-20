/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:07:21 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/19 15:11:16 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	variable_exist(t_tools *tools, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i],
				str, equal_sign(tools->envp[i])) == 0)
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strdup(str);
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
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
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
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
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
	int		i;

	i = 1;
	if (!simple_cmd->str[1] || simple_cmd->str[1][0] == '\0')
		mini_env(tools, simple_cmd);
	else
	{
		while (simple_cmd->str[i])
		{
			if (check_parameter(simple_cmd->str[i]) == 0
				&& variable_exist(tools, simple_cmd->str[i]) == 0)
			{
				if (simple_cmd->str[i])
				{
					tmp = add_var(tools->envp, simple_cmd->str[i]);
					free_arr(tools->envp);
					tools->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
