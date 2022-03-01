/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/25 12:20:04 by mgraaf        ########   odam.nl         */
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
	t_lexor	*lexor_list = NULL;

	if (argc != 1 || argv[1])
	{
		printf("Please do not enter any arguments\n");
		exit(0);
	}
	tools.envp = envp;
	parse_envp(&tools);
	implement_tools(&tools);
	while (1)
	{
		tools.args = readline("minishell$ ");
		add_history(tools.args);
		while (count_quotes(tools.args) % 2 != 0 || tools.args[ft_strlen(tools.args) - 1] == 92)
		{
			if (tools.args[ft_strlen(tools.args) - 1] == 92)
				tools.args = ft_substr(tools.args, 0, ft_strlen(tools.args) - 1);
			tools.args = ft_strjoin(tools.args, readline("> "));
		}
		lexor_list = token_reader(&tools);
		parser(lexor_list, &tools);
		executor(&tools);
		free(tools.args);
	}
	return (0);
}
