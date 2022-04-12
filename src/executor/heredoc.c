/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:42:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/12 14:47:03 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	create_heredoc(t_heredoc *heredoc)
{
	int		fd;
	char	*line;
	int		del_len;

	del_len = ft_strlen(heredoc->del);
	fd = open("build/tmp_heredoc_file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd("heredoc>  ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(heredoc->del, line, del_len))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("heredoc>  ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	return (fd);
}

int	read_heredoc(int fd, t_heredoc *heredoc)
{
	
}

int	ft_heredoc(t_tools *tools, t_simple_cmds *cmd, t_heredoc *heredoc)
{
	int	fd;
	
	fd = create_heredoc(heredoc);
	read_heredoc(fd, heredoc);
	return (EXIT_SUCCESS);
}
