/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/25 12:46:50 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	expander_loop(t_tools *tools, t_simple_cmds *tmp, int i)
{
	int	j;

	j = 0;
	while (tools->envp[j])
	{
		if (ft_strncmp(tmp->str[i] + 1,
				tools->envp[j], equal_sign(tools->envp[j]) - 1) == 0
			&& equal_sign(tools->envp[j])
			== ft_strlen(tmp->str[i]))
		{
			free(tmp->str[i]);
			tmp->str[i] = ft_substr(tools->envp[j],
					equal_sign(tools->envp[j]),
					ft_strlen(tools->envp[j]));
		}
		j++;
	}
}

void	expander(t_tools *tools, t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = simple_cmds;
	while (tmp)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i][0] == '$')
			{
				expander_loop(tools, tmp, i);
			}
			i++;
		}
		tmp = tmp->next;
	}
}
