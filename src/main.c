/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/03/02 11:59:16 by fpolycar      ########   odam.nl         */
=======
/*   Updated: 2022/03/01 16:35:49 by mgraaf        ########   odam.nl         */
>>>>>>> maia
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

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	t_lexor	*lexor_list;

	lexor_list = NULL;
	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	tools.envp = envp;
	parse_envp(&tools);
	implement_tools(&tools);
	while (1)
	{
		tools.args = readline("minishell$ ");
		add_history(tools.args);
		lexor_list = token_reader(&tools);
		parser(lexor_list, &tools);
		// executor(&tools);
		free(tools.args);
	}
	return (0);
}