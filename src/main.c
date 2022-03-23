/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/23 15:17:36 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);
int	implement_tools(t_tools *tools);
char	**ft_arrdup(char **arr);

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	int		i;

	i = 0;
	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	tools.envp = ft_arrdup(envp);
	// printf("%s\n\n", tools.envp[0])
	parse_envp(&tools);
	implement_tools(&tools);
	minishell_loop(&tools);
	return (0);
}
