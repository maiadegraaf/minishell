/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putunsignedint_fd.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:18:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:18:20 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putunsignedint_fd(unsigned int n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}
