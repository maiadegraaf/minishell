/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:39:57 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/18 16:41:00 by mgraaf        ########   odam.nl         */
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

int	handle_infile(t_tools *tools, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_error(7, tools));
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return (ft_error(4, tools));
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_outfile(t_lexor *redirection, t_tools *tools)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
		return (ft_error(7, tools));
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
		return (ft_error(4, tools));
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_simple_cmds *cmd, t_tools *tools)
{
	t_lexor	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS)
			handle_infile(tools, cmd->redirections->str);
		else if (cmd->redirections->token == GREAT
			|| cmd->redirections->token == GREAT_GREAT)
			handle_outfile(cmd->redirections, tools);
		else if (cmd->redirections->token == LESS_LESS)
			handle_infile(tools, cmd->hd_file_name);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
