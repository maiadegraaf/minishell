/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:46:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/23 12:16:34 by fpolycar      ########   odam.nl         */
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
# include "parser.h"
# include "utils.h"
# include "lexor.h"
# include "builtins.h"

int		parse_envp(t_tools *tools);
int		find_pwd(t_tools *tools);
int		count_quotes(char *line);
void	delete_char(char *str, char c);

//builtins
int	(*builtin_arr(char *str))(t_tools *tools);

#endif