/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/17 18:00:06 by mgraaf        ########   odam.nl         */
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
	// int		(*f)(t_tools *);
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
		line = readline(">> ");
		add_history(line);
		tools.args = line;
		token_reader(&tools);
		// f = builtin_arr(tools.args[0]);
		// if (!f(&tools))
		// {	
		// 	printf("HELLO\n");
		// 	process = fork();
		// 	if (process == 0)
		// 		find_cmd(&tools);
		// 	waitpid(process, &status, 0);
		// }
		free(line);
	}
	return (0);
}
