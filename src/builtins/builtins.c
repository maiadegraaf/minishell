/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 11:42:32 by mgraaf        #+#    #+#                 */
<<<<<<< HEAD:srcs/builtins/builtins.c
/*   Updated: 2022/02/24 15:04:55 by mgraaf        ########   odam.nl         */
=======
/*   Updated: 2022/02/24 15:09:05 by alfred        ########   odam.nl         */
>>>>>>> 13faa8f204671af4932f2f2f0432effe154044f3:src/builtins/builtins.c
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_path(t_tools *tools)
{
	tools->old_pwd = tools->pwd;
	tools->pwd = getcwd(NULL, sizeof(NULL));
}

int	(*builtin_arr(char *str))(t_tools *tools)
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
		if (!ft_strncmp(builtins[i][0], str, ft_strlen(str)))
			return (builtins[i][1]);
		i++;
	}
	return (NULL);
}
