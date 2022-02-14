/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:18:06 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:18:08 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			len += ft_determine_type(format[1], ap);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			len++;
		}
		format++;
	}
	va_end(ap);
	return (len);
}
