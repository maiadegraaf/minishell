/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/13 12:12:35 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	ft_printf(
		"\n\n%s\t   █▀█ █▀▀ █▀▀   █▀█ █▀█ █▀▀ █▀ █▀▀ █▄░█ ▀█▀ █▀ \n",
		LIGHT_MAGENTA);
	ft_printf(
		"\t   █▀▀ █▀░ █▄▄   █▀▀ █▀▄ ██▄ ▄█ ██▄ █░▀█ ░█░ ▄█ \n\n");
	ft_printf(
		"%s███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n",
		MAGENTA);
	ft_printf(
		"████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n");
	ft_printf(
		"██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n");
	ft_printf(
		"██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n");
	ft_printf(
		"██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n");
	ft_printf(
		"╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝");
	ft_printf("\n\n%s", RESET_COLOR);
}

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
	init_signals();
	parse_envp(&tools);
	implement_tools(&tools);
	print_welcome();
	minishell_loop(&tools);
	return (0);
}
