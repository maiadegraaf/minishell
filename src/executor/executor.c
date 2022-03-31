/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/31 16:43:13 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	int		i;
	char	*mycmd;

	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
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
			find_cmd(tools->simple_cmds, tools, end, fd_in);
		close(end[1]);
		if (tools->simple_cmds->prev)
			close(fd_in);
		fd_in = end[0];
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
		else
			break ;
	}
	waitpid(ret, &status, 0);
	tools->simple_cmds = ft_simple_cmdsfirst(tools->simple_cmds);
	return (0);
}
