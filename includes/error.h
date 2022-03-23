/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 10:20:00 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/22 17:02:46 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

void	parser_error(int error, t_tools *tools, t_lexor *lexor_list);
void	lexor_error(int error, t_tools *tools);
void	ft_error(int error, t_tools *tools);

#endif