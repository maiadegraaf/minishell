/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_unset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:13:32 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/14 15:04:20 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**whileloop_del_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& str[equal_sign(arr[i])] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_arr(rtn);
				return (rtn);
			}
			j++;
		}	
		i++;
	}
	return (rtn);
}

char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

int	mini_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;

	if (!simple_cmd->str[1])
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (equal_sign(simple_cmd->str[1]) != 0)
	{
		ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		tmp = del_var(tools->envp, simple_cmd->str[1]);
		free_arr(tools->envp);
		tools->envp = tmp;
	}
	return (EXIT_SUCCESS);
}
