/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:06:58 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/12 16:24:22 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexor_list = NULL;
	tools->end = false;
	tools->reset = false;
	tools->pid = NULL;
	return (1);
}

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	implement_tools(tools);
	tools->reset = true;
	if (tools->pid)
	{
		free(tools->pid);
		tools->pid = NULL;
	}
	// system("leaks minishell");
	if (tools->end == true)
		exit (EXIT_SUCCESS);
	minishell_loop(tools);
	return (1);
}

int	minishell_loop(t_tools *tools)
{
	// signal(SIGQUIT, sigint_handler);
	tools->args = readline("minishell$ ");
	add_history(tools->args);
	if (!count_quotes(tools->args))
		ft_error(2, tools);
	if (!token_reader(tools))
		ft_error(1, tools);
	parser(tools);
	if (tools->pipes == 0)
		single_cmd(tools->simple_cmds, tools);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 2);
		if (!tools->pid)
			ft_error(1, tools);
		executor(tools);
	}
	reset_tools(tools);
	return (1);
}
