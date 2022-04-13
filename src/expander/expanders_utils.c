/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanders_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 16:08:47 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/13 11:16:03 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"')
		i++;
	return (i);
}

char	*delete_quotes(char *str, char c)
{
	while (str == ft_strchr(str, c))
		ft_strlcpy(str, str + 1, ft_strlen(str) - 1);
	return (str);
}
