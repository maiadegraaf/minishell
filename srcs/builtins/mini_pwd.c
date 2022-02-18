/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_pwd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 10:13:08 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 10:13:27 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_pwd(t_tools *tools)
{
	printf("%s\n", tools->pwd);
	return (1);
}
