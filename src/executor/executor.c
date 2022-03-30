/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/30 14:57:22 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(char **args, char **paths, char **envp)
{
	int		i;
	char	*mycmd;

	i = 0;
	fprintf(stderr, "in find_cmd\n");
	while (paths[i])
	{
		mycmd = ft_strjoin(paths[i], args[0]);
		fprintf(stderr, "%i\n", i);
		if (!access(mycmd, F_OK))
			execve(mycmd, args, envp);
		free(mycmd);
		i++;
	}
	printf("HELO\n");
	return (1);
}

int	executor(t_tools *tools)
{

	return (0);
}
