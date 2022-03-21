/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 12:04:00 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/21 12:04:46 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	implement_tools(tools);
	tools->pipes = 0;
	minishell_loop(tools);
	// exit (EXIT_SUCCESS);
	return (1);
}

int	implement_tools(t_tools *tools)
{
	tools->in = dup(0);
	tools->out = dup(1);
	tools->err = dup(2);
	tools->simple_cmds = NULL;
	tools->lexor_list = NULL;
	return (1);
}

int	minishell_loop(t_tools *tools)
{
	// int	(*builtin)(t_tools *, struct s_simple_cmds *);

	tools->args = readline("minishell$ ");
	add_history(tools->args);
	if (!count_quotes(tools->args))
		ft_error(2, tools);
	if (!token_reader(tools))
		ft_error(1, tools);
	tools->simple_cmds = parser(tools);
	// printf("str= %s\n", *tools->simple_cmds->str);
	builtin_arr(*tools->simple_cmds->str)(tools, tools->simple_cmds);
	// if (builtin)
	// {
	// 	printf("BUITLIN")
	// 	builtin
	// }
	// system("leaks minishell");
	// ft_lexorclear(&lexor_list);
	// executor(&tools);
	reset_tools(tools);
	return (1);
}