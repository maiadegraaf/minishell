/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:39:57 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/10/03 17:56:15 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_append_outfile(t_lexer *redirections)
{
	int	fd;

	if (redirections->token == GREAT_GREAT)
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_outfile(t_lexer *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_simple_cmds *cmd)
{
	t_lexer	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS)
		{
			if (handle_infile(cmd->redirections->str))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == GREAT
			|| cmd->redirections->token == GREAT_GREAT)
		{
			if (handle_outfile(cmd->redirections))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == LESS_LESS)
		{
			if (handle_infile(cmd->hd_file_name))
				return (EXIT_FAILURE);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
