/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/24 17:33:48 by mgraaf        ########   odam.nl         */
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
	char	*line;
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
		line = readline("minishell$ ");
		add_history(line);
		while (count_quotes(line) % 2 != 0 || line[ft_strlen(line) - 1] == 92)
		{
			if (line[ft_strlen(line) - 1] == 92)
				line = ft_substr(line, 0, ft_strlen(line) - 1);
			line = ft_strjoin(line, readline("> "));
		}
		tools.args = line;
		lexor_list = token_reader(&tools);
		parser(lexor_list, &tools);
		executor(&tools);
		free(line);
	}
	return (0);
}
