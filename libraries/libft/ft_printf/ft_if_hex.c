/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_if_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:17:54 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:17:56 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_if_hex(char c, va_list ap)
{
	char	*up;
	char	*low;

	up = "0123456789ABCDEF";
	low = "0123456789abcdef";
	if (c == 'x')
		return (ft_convert_hex(va_arg(ap, unsigned int), low));
	if (c == 'X')
		return (ft_convert_hex(va_arg(ap, unsigned int), up));
	if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (2 + ft_convert_hex(va_arg(ap, unsigned long), low));
	}
	return (0);
}
