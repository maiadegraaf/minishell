/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:11:56 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 10:13:38 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_export(t_tools *tools)
{
	printf("%s\n", tools->pwd);
	return (1);
}
