/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_envp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 16:16:57 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/17 16:17:02 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	char	*path_from_envp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path_from_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	return (path_from_envp);
}

char	**parse_envp(char **argv, char **envp)
{
	char	*path_from_envp;
	char	**mypaths;
	int		i;
	char	*tmp;

	path_from_envp = find_path(envp);
	mypaths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (mypaths[i])
	{
		if (ft_strncmp(&mypaths[i][ft_strlen(mypaths[i]) - 1], "/", 1) != 0)
		{
			tmp = ft_strjoin(mypaths[i], "/");
			free(mypaths[i]);
			mypaths[i] = tmp;
		}
		i++;
	}
	return (mypaths);
}
