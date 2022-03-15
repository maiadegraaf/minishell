/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:10:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/15 13:25:45 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//probably have to add some frees in here.

int	mini_exit(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void) simple_cmd;
	free(tools->args);
	exit(0);
	return (1);
}
