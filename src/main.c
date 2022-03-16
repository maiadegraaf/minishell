/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/16 10:28:20 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_tools(t_tools *tools)
{
	tools->in = dup(0);
	tools->out = dup(1);
	tools->err = dup(2);
	return (1);
}

int	minishell_loop(t_tools *tools)
{
	t_lexor	*lexor_list;

	lexor_list = NULL;
	tools->args = readline("minishell$ ");
	add_history(tools->args);
	lexor_list = token_reader(tools);
	parser(lexor_list, tools);
	// executor(&tools);
	free(tools->args);
	minishell_loop(tools);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	tools.envp = envp;
	parse_envp(&tools);
	implement_tools(&tools);
	minishell_loop(&tools);
	return (0);
}
