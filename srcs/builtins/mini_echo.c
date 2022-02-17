/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 10:19:09 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_echo(t_tools *tools)
{
	if (ft_strncmp(tools->args[1], "-n", ft_strlen(tools->args[1])))
		printf("%s", tools->args[2]);
	else
		printf("%s\n", tools->args[2]);
	return (1);
}
