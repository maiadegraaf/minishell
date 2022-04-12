/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 17:42:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/12 10:20:29 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

char	*find_del(char *heredoc_cmd)
{
	char	*del;

	del = ft_strnstr(heredoc_cmd, "\"|\"", ft_strlen(heredoc_cmd));
	del = ft_strtrim(del, "|\"");
	return (del);
}

int	ft_heredoc(t_tools *tools, t_simple_cmds *cmd, char *heredoc_cmd)
{
	int		fd;
	char	*line;
	char	*del;
	int		del_len;

	(void) tools;
	(void) cmd;
	del = find_del(heredoc_cmd);
	printf("%s\n", del);
	del_len = ft_strlen(del);
	fd = open("build/tmp_heredoc_file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = get_next_line(STDIN_FILENO);
	write(fd, line, ft_strlen(line));
	while (ft_strncmp(del, line, del_len))
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		// line = expander(tools, line);
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int main(void)
{
	t_tools tools;
	t_simple_cmds cmd;
	ft_heredoc(&tools, &cmd, "\"echo\"|\"EOF\"");
}
