/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 10:20:00 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/10/03 17:56:15 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

void	parser_error(int error, t_tools *tools, t_lexer *lexer_list);
int		parser_double_token_error(t_tools *tools, t_lexer *lexer_list,
			t_tokens token);
void	lexer_error(int error, t_tools *tools);
int		cmd_not_found(char *str);
int		export_error(char *c);

//ft_error
int		ft_error(int error, t_tools *tools);

#endif