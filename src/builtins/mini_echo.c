/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 10:47:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/29 17:03:07 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

int	mini_echo(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	i = 1;
	(void) tools;
	if (!simple_cmd->str[i])
	{
		ft_putchar_fd('\n', tools->out);
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(simple_cmd->str[1], "-n", ft_strlen(simple_cmd->str[1])))
		print_lines(2, simple_cmd->str, tools->out);
	else
	{
		print_lines(1, simple_cmd->str, tools->out);
		ft_putchar_fd('\n', tools->out);
	}
	return (EXIT_SUCCESS);
}
