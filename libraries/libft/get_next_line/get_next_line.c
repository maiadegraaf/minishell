/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:18:35 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:18:37 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_check_nl(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

char	*ft_send_join(char *s1, char *s2)
{
	if (!s1)
		s1 = ft_strdup("");
	if (!s1 && !s2)
		return (NULL);
	return (ft_g_strjoin(s1, s2));
}

char	*read_buff(int fd, char *saved)
{
	char		buff[11];
	int			i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buff, 10);
		if (i >= 0)
			buff[i] = '\0';
		if (i < 0)
			return (NULL);
		saved = ft_send_join(saved, buff);
		if (ft_check_nl(saved) > 0)
			break ;
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*ret;

	if (ft_check_nl(saved) == 0)
		saved = read_buff(fd, saved);
	if (!saved)
		return (NULL);
	ret = ft_create_line(saved);
	saved = ft_remove_line(saved);
	return (ret);
}
