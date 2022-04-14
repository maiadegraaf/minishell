/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/13 16:02:19 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexor	*start;

	cmd->str = expander(tools, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		cmd->redirections->str
			= expander_str(tools, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (tools->reset == true)
	{
		i = 0;
		tools->reset = false;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
		ft_error(5, tools);
	if (tools->pid[i] == 0)
		dup_cmd(cmd, tools, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	executor(t_tools *tools)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (tools->simple_cmds)
	{
		tools->simple_cmds = call_expander(tools, tools->simple_cmds);
		if (tools->simple_cmds->next)
			pipe(end);
		ft_fork(tools, end, fd_in, tools->simple_cmds);
		close(end[1]);
		if (tools->simple_cmds->prev)
			close(fd_in);
		fd_in = end[0];
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(tools->pid, tools->pipes);
	tools->simple_cmds = ft_simple_cmdsfirst(tools->simple_cmds);
	return (0);
}
