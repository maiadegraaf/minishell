/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 15:20:00 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/17 11:25:57 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"

//builtins
void	change_path(t_tools *tools);

int		mini_echo(t_tools *tools);

int		mini_cd(t_tools *tools);

int		mini_pwd(t_tools *tools);

int		mini_export(t_tools *tools);

int		mini_unset(t_tools *tools);

int		mini_env(t_tools *tools);

int		mini_exit(t_tools *tools);

#endif