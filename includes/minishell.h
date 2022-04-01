/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:46:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/31 17:21:59 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "pipex.h"
# include "parser.h"
# include "utils.h"
# include "error.h"
# include "lexor.h"
# include "builtins.h"
# include "executor.h"

int		parse_envp(t_tools *tools);
int		find_pwd(t_tools *tools);
int		reset_tools(t_tools *tools);
void	init_stri(int i, int j, t_tools *tools);
void	expander(t_tools *tools);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);
int		after_dollar_lenght(char *str, int j);
void	free_things(char *tmp2, t_tools *tools, int i);

//builtins
int		(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd);

#endif