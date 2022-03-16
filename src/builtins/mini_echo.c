/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/15 14:50:27 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_lines(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], STDOUT_FILENO)
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	mini_echo(t_tools *tools, t_simple_cmds *simple_cmd)
{
	if (!ft_strncmp(&tools->args[1], "-n", ft_strlen(&tools->args[1])))
		print_lines(2, &tools->args, 1);
	else
	{
		print_lines(1, &tools->args, 1);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (1);
}
