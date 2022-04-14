/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:04:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/13 14:39:04 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrap_line(char *line, char *color)
{
	printf("\n%s║\t", LIGHT_CYAN);
	printf("%s%s", color, line);
	printf("%s\t ║", LIGHT_CYAN);
}

void	print_presents(void)
{
	printf("\n%s║\t\t\t\t\t\t\t\t\t\t ║", LIGHT_CYAN);
	wrap_line(
		"\t   █▀█ █▀▀ █▀▀   █▀█ █▀█ █▀▀ █▀ █▀▀ █▄░█ ▀█▀ █▀\t\t",
		LIGHT_MAGENTA);
	wrap_line(
		"\t   █▀▀ █▀░ █▄▄   █▀▀ █▀▄ ██▄ ▄█ ██▄ █░▀█ ░█░ ▄█\t\t",
		LIGHT_MAGENTA);
	printf("\n%s║\t\t\t\t\t\t\t\t\t\t ║", LIGHT_CYAN);
}

void	print_minishell(void)
{
	wrap_line(
		"███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░",
		MAGENTA);
	wrap_line(
		"████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░",
		MAGENTA);
	wrap_line(
		"██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░",
		MAGENTA);
	wrap_line(
		"██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░",
		MAGENTA);
	wrap_line(
		"██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗",
		MAGENTA);
	wrap_line(
		"╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝",
		MAGENTA);
}

void	print_welcome(void)
{
	printf("\n%s╔═════════════════════════════════════════════",
		LIGHT_CYAN);
	printf("═══════════════════════════════════╗");
	print_presents();
	print_minishell();
	printf("\n%s║\t\t\t\t\t\t\t\t\t\t ║\n", LIGHT_CYAN);
	printf("╚═══════════════════════════════════════");
	printf("═════════════════════════════════════════╝\n");
	printf("\n\n%s", RESET_COLOR);
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
