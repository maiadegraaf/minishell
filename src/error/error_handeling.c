/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handeling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 09:57:33 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/16 15:14:40 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/* 
TO DO

-> Incorrect input handleing
	-> Parser
		-> No str after token
-> Malloc error handeling
	-> Lexor
	-> Parser
		-> Redirections
*/

void	lexor_error(t_lexor **lexor_list, t_tools *tools)
{
	ft_lexorclear(lexor_list);
	ft_error(1, tools);
}

/**
 * @brief 
 * Finds corresponding error and frees args;
 * @param error 
 * Number of related error:
 * 0 = If there is no string following a redirection or a pipe.
 * @param tools 
 */
void	ft_error(int error, t_tools *tools)
{
	(void) tools;
	if (error == 0)
		printf("syntax error: unexpected 'newline'\n");
	else if (error == 1)
		printf("memory error: unable to assign memory\n");
	else if (error == 2)
		printf("syntax error: unable to locate closing quotation\n");
}
