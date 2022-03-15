/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_cd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 15:17:04 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/15 12:53:17 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd)
{
	if (chdir(&tools->args[1]))
		perror("cd");
	change_path(tools);
	return (1);
}
