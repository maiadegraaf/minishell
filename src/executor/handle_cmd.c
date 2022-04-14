/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:24:04 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/13 16:06:06 by maiadegraaf   ########   odam.nl         */
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->str[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (1);
}

void	handle_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	if (cmd->heredoc)
		send_heredoc(tools, cmd);
	if (cmd->redirections)
		handle_redirections(cmd, tools);
	if (cmd->builtin)
	{
		cmd->builtin(tools, cmd);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->str[0][0] != '\0')
		find_cmd(cmd, tools);
}

void	dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, tools);
}

void	single_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int	pid;
	int	status;

	tools->simple_cmds = call_expander(tools, tools->simple_cmds);
	if (cmd->builtin)
	{
		cmd->builtin(tools, cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
		ft_error(5, tools);
	if (pid == 0)
		handle_cmd(cmd, tools);
	waitpid(pid, &status, 0);
}
