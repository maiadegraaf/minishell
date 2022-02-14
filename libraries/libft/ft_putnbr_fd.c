/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:23:40 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:23:42 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	j;

	j = (long long)n;
	if (j < 0)
	{
		ft_putchar_fd('-', fd);
		j *= -1;
	}
	if (j < 10)
		ft_putchar_fd(j + '0', fd);
	if (j >= 10)
	{
		ft_putnbr_fd(j / 10, fd);
		ft_putchar_fd((j % 10) + '0', fd);
	}
}
