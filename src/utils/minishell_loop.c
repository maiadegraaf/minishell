/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:06:58 by fpolycar      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/04/01 16:08:32 by fpolycar      ########   odam.nl         */
=======
/*   Updated: 2022/03/31 17:24:49 by maiadegraaf   ########   odam.nl         */
>>>>>>> maia_2
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexor_list = NULL;
	tools->end = false;
	return (1);
}

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	implement_tools(tools);
	tools->pipes = 0;
	// system("leaks minishell");
	if (tools->end == true)
		exit (EXIT_SUCCESS);
	minishell_loop(tools);
	return (1);
}

int	minishell_loop(t_tools *tools)
{
	tools->args = readline("minishell$ ");
	add_history(tools->args);
	if (!count_quotes(tools->args))
		ft_error(2, tools);
	if (!token_reader(tools))
		ft_error(1, tools);
	parser(tools);
	if (dollar_sign(tools->args) != 0)
		expander(tools);
	builtin_arr(tools->simple_cmds->str[0])(tools, tools->simple_cmds);
	// executor(tools);
	reset_tools(tools);
	return (1);
}