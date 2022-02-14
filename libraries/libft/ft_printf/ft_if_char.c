/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_if_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:17:46 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:17:49 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_if_char(char c, va_list ap)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	if (c == 's')
		return (ft_putstr_size(va_arg(ap, char *), 1));
	return (0);
}
