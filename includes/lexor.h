/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexor.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:55:06 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/16 12:50:20 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXOR_H
# define LEXOR_H
# include "minishell.h"

// typedef struct s_lexor
// {
// 	char			*str;
// 	t_tokens		token;
// 	struct s_lexor	*next;
// }	t_lexor;

//handle_tokens

int		handle_quotes_inside_word(int i, char *str, char del);
int		handle_quotes(int i, char *str, char del, t_lexor **lexor_list);

#endif