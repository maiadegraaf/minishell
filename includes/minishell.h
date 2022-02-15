/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:46:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/14 18:06:02 by mgraaf        ########   odam.nl         */
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

typedef struct s_tools
{
	char	**args;
	char	**paths;
	char	**envp;
}	t_tools;

char	**parse_envp(char **envp);

#endif