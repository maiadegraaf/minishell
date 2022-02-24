/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 11:17:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/02/23 12:19:51 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			nb++;
		i++;
	}
	return (nb);
}

void	delete_char(char *str, char c)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == c)
		{
			j = i;
			while (j < len)
			{
				str[i] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}
