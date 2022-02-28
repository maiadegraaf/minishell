/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:10:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 10:22:38 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//probably have to add some frees in here.

int	mini_exit(t_tools *tools)
{
	free(tools->args);
	exit(0);
	return (1);
}
