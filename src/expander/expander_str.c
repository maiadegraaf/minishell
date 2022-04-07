/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_str.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 15:49:23 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/07 15:49:35 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	loop_if_dollar_sign_str(t_tools *tools, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str + j + 1,
				tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
			&& after_dollar_lenght(str, j) - j
			== (int) equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			*tmp = ft_strjoin(*tmp, tmp2);
			free(tmp2);
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dollar_lenght(str, j) - j;
	return (ret);
}

char	*detect_dollar_sign_str(t_tools *tools, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		if (str[j] == '$')
			j += loop_if_dollar_sign_str(tools, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j]);
			if (!tmp)
				tmp = ft_strdup(tmp2);
			else
				tmp = ft_strjoin(tmp, tmp2);
			free(tmp2);
		j++;
		}
	}
	return (tmp);
}

char	*expander_str(t_tools *tools, char *str)
{
	if (str[ft_strlen(str) - 1] != '\'' && dollar_sign(str) != 0)
		str = detect_dollar_sign_str(tools, str);
	return (str);
}
