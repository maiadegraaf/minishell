/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:06:58 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/31 16:43:58 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexor_list = NULL;
	return (1);
}

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	implement_tools(tools);
	tools->pipes = 0;
	// system("leaks minishell");
	minishell_loop(tools);
	// exit (EXIT_SUCCESS);
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
	// expander(tools, tools->simple_cmds);
	// printf("%s\n", *tools->simple_cmds->str);
	executor(tools);
	reset_tools(tools);
	return (1);
}