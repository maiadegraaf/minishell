/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/01 16:08:06 by fpolycar      ########   odam.nl         */
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
	int	i;

	i = 1;
	(void) tools;
	if (!simple_cmd->str[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(simple_cmd->str[1], "-n", ft_strlen(simple_cmd->str[1])))
		print_lines(2, simple_cmd->str, STDOUT_FILENO);
	else
	{
		print_lines(1, simple_cmd->str, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
