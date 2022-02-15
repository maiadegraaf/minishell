/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:46:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/15 17:42:00 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libraries/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/pipex/pipex.h"
//# include "builtins.h"

typedef struct s_tools
{
	char	**args;
	char	**paths;
	char	**envp;
	int		in;
	int		out;
	int		err;
	char	*pwd;
	char	*old_pwd;

}	t_tools;

int		parse_envp(t_tools *tools);
int		find_pwd(t_tools *tools);

#endif