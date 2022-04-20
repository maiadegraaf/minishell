/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:22:38 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:22:40 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*new_element;

	new_element = (struct s_list *)malloc(sizeof(struct s_list));
	if (!new_element)
		return (0);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
