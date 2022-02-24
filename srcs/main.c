/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/24 15:40:34 by alfred        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	find_cmd(t_tools *tools)
// {
// 	int		i;
// 	char	*mycmd;

// 	i = 0;
// 	while ((tools->paths)[i])
// 	{
// 		mycmd = ft_strjoin((tools->paths)[i], (tools->args)[0]);
// 		if (!access(mycmd, F_OK))
// 			execve(mycmd, tools->args, tools->envp);
// 		free(mycmd);
// 		i++;
// 	}
// 	return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;
	t_lexor	*lexor_list = NULL;
	// pid_t	process;
	// int		status;

	if (argc != 1 || argv[1])
	{
		printf("Please do not enter any arguments\n");
		exit(0);
	}
	tools.envp = envp;
	parse_envp(&tools);
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
		line = delete_char(line, '\\');
		tools.args = line;
		lexor_list = token_reader(&tools);
		parser(lexor_list);
		// while (lexor_list)
		// {
		// 	printf("str = %s \t token = %d\n", lexor_list->str, lexor_list->token);
		// 	lexor_list = lexor_list->next;
		// }
		free(line);
	}
	return (0);
}
