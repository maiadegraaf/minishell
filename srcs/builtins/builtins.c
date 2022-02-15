/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 11:42:32 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/15 18:02:20 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_path(t_tools *tools)
{
	tools->old_pwd = tools->pwd;
	tools->pwd = getcwd(NULL, 200);
}

void	*init_builtin_arr(char *str)
{
	static void	*builtins[7][2] = {
	{"echo", mini_echo},
	{"cd", mini_cd},
	{"pwd", mini_pwd},
	{"export", mini_export},
	{"unset", mini_unset},
	{"env", mini_env},
	{"exit", mini_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(builtins[i][0], str, strlen(builtins[i][0])))
			return (builtins[i][1]);
		i++;
	}
	return (NULL);
}
