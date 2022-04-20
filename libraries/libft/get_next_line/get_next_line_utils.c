/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:18:30 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:18:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_g_strjoin(char *s1, char *s2)
{
	char	*s1_2;
	int		i;
	int		j;

	s1_2 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!s1_2)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1_2[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1_2[i + j] = s2[j];
		j++;
	}	
	s1_2[i + j] = '\0';
	free(s1);
	return (s1_2);
}

char	*ft_create_line(char *saved)
{	
	int		line_len;
	int		i;
	char	*temp;

	i = 0;
	if (!saved[i])
		return (NULL);
	line_len = ft_check_nl(saved);
	if (line_len == 0)
		line_len = ft_strlen(saved);
	temp = malloc (line_len * sizeof(char) + 1);
	if (!temp)
		return (NULL);
	while (i < line_len && saved[i])
	{
		temp[i] = saved[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_remove_line(char *saved)
{
	int		line_len;
	int		i;
	char	*temp;

	i = 0;
	line_len = ft_check_nl(saved);
	if (!line_len)
	{
		free(saved);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(saved) - line_len + 1));
	if (!temp)
		return (NULL);
	while (saved[line_len + i])
	{
		temp[i] = saved[line_len + i];
		i++;
	}
	temp[i] = '\0';
	free(saved);
	return (temp);
}
