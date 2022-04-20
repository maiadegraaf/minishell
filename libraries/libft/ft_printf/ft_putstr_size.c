/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_size.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:18:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:18:13 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_size(char *s, int fd)
{
	int	i;

	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
