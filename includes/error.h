/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 10:20:00 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/16 13:03:36 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

void	lexor_error(t_lexor **lexor_list, t_tools *tools);
void	ft_error(int error, t_tools *tools);

#endif