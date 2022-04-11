/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:39:57 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/31 17:46:29 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_append_outfile(t_lexor *redirections)
{
	int	fd;

	if (redirections->token == GREAT)
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
	else
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	check_outfile(t_lexor *redirections)
{
	t_lexor	*start;
	int		fd;

	start = redirections;
	fd = 0;
	while (redirections)
	{
		if (redirections->token == GREAT
			|| redirections->token == GREAT_GREAT)
		{
			fd = check_append_outfile(redirections);
			if (fd < 0)
				return (-1);
		}
		redirections
			= redirections->next;
	}
	redirections = start;
	return (fd);
}

int	check_infile(t_lexor *redirections)
{
	t_lexor	*start;
	int		fd;

	start = redirections;
	fd = 0;
	while (redirections)
	{
		if (redirections->token == LESS)
		{
			fd = open(redirections->str, O_RDONLY);
			if (fd < 0)
				return (-1);
		}
		redirections
			= redirections->next;
	}
	redirections = start;
	return (fd);
}

int	handle_redirections(t_simple_cmds *cmd, t_tools *tools)
{
	int	fd_in;
	int	fd_out;

	fd_in = check_infile(cmd->redirections);
	if (fd_in < 0)
		ft_error(7, tools);
	if (fd_in > 0 && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	if (fd_in > 0)
		close(fd_in);
	fd_out = check_outfile(cmd->redirections);
	if (fd_out < 0)
		ft_error (6, tools);
	if (fd_out > 0 && dup2(fd_out, STDOUT_FILENO) < 0)
		ft_error(4, tools);
	if (fd_out > 0)
		close(fd_out);
	return (EXIT_SUCCESS);
}
