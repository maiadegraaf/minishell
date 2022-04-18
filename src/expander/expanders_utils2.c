/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanders_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 16:20:01 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/18 16:32:01 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(g_global.error_num);
	return (ft_strlen(*tmp) + 1);
}
