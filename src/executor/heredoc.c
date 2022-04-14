/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:42:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/14 13:17:41 by mgraaf        ########   odam.nl         */
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
	ft_putstr_fd("\033[1;34m> \033[0m", STDERR_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(heredoc->del, line, del_len))
	{
		if (quotes == false)
			line = send_expander(tools, line);
		write(fd, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("\033[1;34m> \033[0m", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	return (EXIT_SUCCESS);
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
	tools->heredoc = true;
	return (EXIT_SUCCESS);
}

int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_heredoc	*start;

	start = cmd->heredoc;
	while (cmd->heredoc)
	{	
		ft_heredoc(tools, cmd->heredoc);
		cmd->heredoc = cmd->heredoc->next;
	}
	cmd->heredoc = start;
	return (EXIT_SUCCESS);
}
