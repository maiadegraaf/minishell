/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:17:39 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/31 17:45:11 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

// check_redirectoins
int	check_outfile(t_lexor *redirections);
int	check_infile(t_lexor *redirections);
int	handle_redirections(t_simple_cmds *cmd, t_tools *tools);

// executor
int	executor(t_tools *tools);

#endif