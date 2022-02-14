/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_convert_hex.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:17:31 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:17:33 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_hex(unsigned long n, char *up_or_low)
{
	if (n != 0)
	{
		ft_print_hex(n / 16, up_or_low);
		ft_putchar_fd(up_or_low[n % 16], 1);
	}
}

int	ft_convert_hex(unsigned long n, char *up_or_low)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		ft_putchar_fd(up_or_low[n], 1);
		return (1);
	}
	ft_print_hex(n, up_or_low);
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
