/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:06:58 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/24 16:06:59 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);

int	implement_tools(t_tools *tools)
{
	tools->in = dup(0);
	tools->out = dup(1);
	tools->err = dup(2);
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
	system("leaks minishell");
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
	builtin_arr(tools->simple_cmds->str[0])(tools, tools->simple_cmds);
	// ft_lexorclear(&lexor_list);
	// executor(&tools);
	reset_tools(tools);
	return (1);
}