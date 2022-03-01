/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 10:59:55 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/15 17:07:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../../libraries/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	**paths;
	int		f1;
	int		f2;
	char	**envp;
	char	**cmds1;
	char	**cmds2;
}	t_pipex;

//char	**parse_envp(char **envp);

#endif