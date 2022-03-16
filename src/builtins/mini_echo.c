/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/16 10:06:58 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_lines(int i, char **str)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], STDOUT_FILENO);
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	mini_echo(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void) simple_cmd;
	if (!ft_strncmp(&tools->args[1], "-n", ft_strlen(&tools->args[1])))
		print_lines(2, &tools->args);
	else
	{
		print_lines(1, &tools->args);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (1);
}
