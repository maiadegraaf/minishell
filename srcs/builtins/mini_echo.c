/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 12:37:55 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_lines(int i, char **str)
{
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
}

int	mini_echo(t_tools *tools)
{
	if (!ft_strncmp(tools->args[1], "-n", ft_strlen(tools->args[1])))
		print_lines(2, tools->args);
	else
	{
		print_lines(1, tools->args);
		printf("\n");
	}
	return (1);
}
