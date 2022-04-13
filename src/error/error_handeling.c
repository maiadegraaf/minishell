/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handeling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 09:57:33 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/13 12:58:02 by maiadegraaf   ########   odam.nl         */
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
int	ft_error(int error, t_tools *tools)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error: unexpected 'newline'\n", STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n", STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	reset_tools(tools);
	return (EXIT_SUCCESS);
}
