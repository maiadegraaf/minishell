/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:42:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/13 15:06:53 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

char	*send_expander(t_tools *tools, char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n");
	free(line);
	line = expander_str(tools, tmp);
	tmp = ft_strjoin(line, "\n");
	free(line);
	return (tmp);
}

int	create_heredoc(t_heredoc *heredoc, bool quotes, t_tools *tools)
{
	int		fd;
	char	*line;
	int		del_len;

	del_len = ft_strlen(heredoc->del);
	fd = open("build/tmp_heredoc_file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd("\033[1;34m> \033[0m", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(heredoc->del, line, del_len))
	{
		if (quotes == false)
			line = send_expander(tools, line);
		write(fd, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("\033[1;34m> \033[0m", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	read_heredoc(t_heredoc *heredoc, t_tools *tools)
{
	int		fd;
	char	**cmds;
	int		i;
	char	*mycmd;

	cmds = ft_split(heredoc->cmd, ' ');
	cmds = expander(tools, cmds);
	fd = open("build/tmp_heredoc_file.txt", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_error(4, tools);
	i = 0;
	while (tools->paths[i])
	{
		mycmd = ft_strjoin(tools->paths[i], cmds[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmds, tools->envp);
		free(mycmd);
		i++;
	}
	close(fd);
	exit(EXIT_FAILURE);
}

int	ft_heredoc(t_tools *tools, t_heredoc *heredoc)
{
	bool	quotes;

	if (heredoc->del[0] == '\"'
		&& heredoc->del[ft_strlen(heredoc->del) - 1] == '\"')
		quotes = true;
	else
		quotes = false;
	create_heredoc(heredoc, quotes, tools);
	if (heredoc->cmd)
		read_heredoc(heredoc, tools);
	return (EXIT_SUCCESS);
}

int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_heredoc	*start;
	int			i;
	int			num_heredocs;

	i = 0;
	start = cmd->heredoc;
	num_heredocs = ft_heredocsize(cmd->heredoc);
	cmd->heredoc_pid = ft_calloc(num_heredocs, sizeof(int));
	while (cmd->heredoc)
	{	
		cmd->heredoc_pid[i] = fork();
		if (cmd->heredoc_pid[i] < 0)
			ft_error(5, tools);
		if (cmd->heredoc_pid[i] == 0)
			ft_heredoc(tools, cmd->heredoc);
		cmd->heredoc = cmd->heredoc->next;
	}
	pipe_wait(cmd->heredoc_pid, num_heredocs);
	cmd->heredoc = start;
	return (EXIT_SUCCESS);
}
