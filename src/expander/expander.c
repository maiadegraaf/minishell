/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/07 13:24:33 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	loop_if_dollar_sign(t_tools *tools, char **str, int j, int i)
{
	int		k;
	int		ret;
	char	*tmp;
	char	*tmp2;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str[i] + j + 1,
				tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
			&& after_dollar_lenght(str[i], j) - j
			== (int) equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp = ft_strjoin(str[i], tmp2);
			free(tmp2);
			str[i] = tmp;
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dollar_lenght(str[i], j) - j;
	return (ret);
}

char	*detect_dollar_sign(t_tools *tools, char **str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = 0;
	tmp = NULL;
	while (str[i][j])
	{
		if (str[i][j] == '$')
			j += loop_if_dollar_sign(tools, str, j, i);
		else
		{
			tmp2 = char_to_str(str[i][j]);
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

char	**expander(t_tools *tools, char **str)
{
	int				i;

	i = 0;
	while (str[i] != NULL)
	{	
		if (str[i][ft_strlen(str[i])] != '\''
			&& dollar_sign(str[i]) != 0)
			str[i] = detect_dollar_sign(tools, str, i);
		i++;
	}
	return (str);
}
