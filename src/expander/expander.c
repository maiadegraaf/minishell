/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/05 17:12:35 by alfred        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	loop_if_dollar_sign(t_tools *tools, char *arr_tmp, int j, int i)
{
	int		k;
	int		ret;
	char	*tmp;
	char	*tmp2;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(arr_tmp + j + 1,
				tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
			&& after_dollar_lenght(arr_tmp, j) - j
			== (int) equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp = ft_strjoin(tools->simple_cmds->str[i], tmp2);
			free_things(tmp2, tools, i);
			tools->simple_cmds->str[i] = tmp;
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dollar_lenght(arr_tmp, j) - j;
	return (ret);
}

char	*detect_dollar_sign(t_tools *tools, int i)
{
	int		j;
	char	*arr_tmp;
	char	*tmp;
	char	*tmp2;

	j = 0;
	arr_tmp = ft_strdup(tools->simple_cmds->str[i]);
	while (arr_tmp[j])
	{
		init_stri(i, j, tools);
		if (arr_tmp[j] == '$')
			j += loop_if_dollar_sign(tools, arr_tmp, j, i);
		else
		{
			tmp2 = char_to_str(arr_tmp[j]);
			tmp = ft_strjoin(tools->simple_cmds->str[i], tmp2);
			free_things(tmp2, tools, i);
			tools->simple_cmds->str[i] = tmp;
			j++;
		}
	}
	free(arr_tmp);
	return (tools->simple_cmds->str[i]);
}

void	expander(t_tools *tools)
{
	int				i;

	i = 0;
	while (tools->simple_cmds->next)
	{
		while (tools->simple_cmds->str[i])
		{
			if (tools->simple_cmds->str[i][0] != '\''
				&& tools->simple_cmds->str[i][ft_strlen(tools->simple_cmds->str[i])] != '\'')
				detect_dollar_sign(tools, i);
			i++;
		}
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
	}
	while (i-- > 0)
		tools->simple_cmds = tools->simple_cmds->prev;
	// printf("%s\n", tools->simple_cmds->str[0]);
	// tools->simple_cmds = ft_simple_cmdsfirst(tools->simple_cmds);
}
