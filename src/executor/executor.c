/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/04 16:11:45 by alfred        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int		i;
	char	*mycmd;

	i = 0;
	while (tools->paths[i])
	{
		mycmd = ft_strjoin(tools->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, tools->envp);
		free(mycmd);
		i++;
	}
	exit(EXIT_FAILURE);
	return (1);
}

void	fork_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	if (cmd->redirections)
		handle_redirections(cmd, tools);
	if (cmd->builtin)
	{
		cmd->builtin(tools, cmd);
		exit(EXIT_SUCCESS);
	}
	else
		find_cmd(cmd, tools);
}

int	executor(t_tools *tools)
{
	int		end[2];
	pid_t	ret;
	int		status;
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (tools->simple_cmds)
	{
		if (tools->simple_cmds->next)
			pipe(end);
		ret = fork();
		if (ret < 0)
			ft_error(5, tools);
		if (ret == 0)
			fork_cmd(tools->simple_cmds, tools, end, fd_in);
		close(end[1]);
		if (tools->simple_cmds->prev)
			close(fd_in);
		fd_in = end[0];
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
		else
			break ;
	}
	tools->end_pid = ret;
	waitpid(ret, &status, 0);
	tools->simple_cmds = ft_simple_cmdsfirst(tools->simple_cmds);
	return (0);
}
