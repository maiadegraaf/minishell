/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 10:20:00 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/18 13:00:42 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

void	parser_error(int error, t_tools *tools, t_lexor *lexor_list);
void	parser_double_token_error(t_tools *tools, t_lexor *lexor_list,
			t_tokens token);
void	lexor_error(int error, t_tools *tools);
int		cmd_not_found(char *str);
int		ft_error(int error, t_tools *tools);

#endif