/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:17:39 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/25 11:53:28 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int	check_outfile(t_tools *tools);
int	check_infile(t_tools *tools);
int	executor(t_tools *tools);

#endif