/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanders_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 16:08:47 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/07 11:40:57 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	init_stri(int i, int j, t_tools *tools)
{
	if (j == 0)
	{
		free(tools->simple_cmds->str[i]);
		tools->simple_cmds->str[i] = ft_strdup("\0");
	}
}

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	after_dollar_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"')
		i++;
	return (i);
}
