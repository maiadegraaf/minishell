/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:22:59 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:23:03 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (((char *)src) || ((char *)dst)))
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return ((void *)dst);
}
