/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:22:33 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:22:35 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*head;

	head = NULL;
	if (!lst || !f)
		return (head);
	while (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		if (new_list)
			ft_lstadd_back(&head, new_list);
		else
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (head);
}
