/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:22:27 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:22:29 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
