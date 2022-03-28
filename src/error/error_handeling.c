/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handeling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 09:57:33 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/25 10:26:44 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	parser_error(int error, t_tools *tools, t_lexor *lexor_list)
{
	ft_lexorclear(&lexor_list);
	ft_error(error, tools);
}

void	lexor_error(int error, t_tools *tools)
{
	ft_lexorclear(&tools->lexor_list);
	ft_error(error, tools);
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
	if (error == 0)
		printf("syntax error: unexpected 'newline'\n");
	else if (error == 1)
		printf("memory error: unable to assign memory\n");
	else if (error == 2)
		printf("syntax error: unable to locate closing quotation\n");
	else if (error == 3)
		printf("Parser problem\n");
	reset_tools(tools);
}
