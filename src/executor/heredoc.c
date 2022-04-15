/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:42:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/15 14:34:29 by mgraaf        ########   odam.nl         */
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

int	create_heredoc(t_heredoc *heredoc, bool quotes,
	t_tools *tools, char *file_name)
{
	int		fd;
	char	*line;
	int		del_len;

	del_len = ft_strlen(heredoc->del);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd("\033[1;34m> \033[0m", STDERR_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && (ft_strncmp(heredoc->del, line, ft_strlen(line) - 1)
			|| ft_strncmp(heredoc->del, line, del_len))
		&& !g_global.stop_heredoc)
	{
		if (quotes == false)
			line = send_expander(tools, line);
		write(fd, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("\033[1;34m> \033[0m", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	if (!line)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_tools *tools, t_heredoc *heredoc, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if (heredoc->del[0] == '\"'
		&& heredoc->del[ft_strlen(heredoc->del) - 1] == '\"')
		quotes = true;
	else
		quotes = false;
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, tools, file_name);
	g_global.in_heredoc = 0;
	tools->heredoc = true;
	return (sl);
}

int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_heredoc	*start;
	static int	i = 0;
	char		*num;
	int			sl;

	start = cmd->heredoc;
	sl = EXIT_SUCCESS;
	while (cmd->heredoc)
	{	
		if (cmd->hd_file_name)
			free(cmd->hd_file_name);
		num = ft_itoa(i++);
		cmd->hd_file_name = ft_strjoin("build/.tmp_heredoc_file", num);
		free(num);
		sl = ft_heredoc(tools, cmd->heredoc, cmd->hd_file_name);
		if (sl)
		{
			g_global.error_num = 1;
			return (reset_tools(tools));
		}
		cmd->heredoc = cmd->heredoc->next;
	}
	cmd->heredoc = start;
	return (EXIT_SUCCESS);
}
