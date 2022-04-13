/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_lexor_clear_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 11:11:43 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/13 11:14:20 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_lexor	*ft_lexorclear_one(t_lexor **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	ft_lexordel_first(t_lexor **lst)
{
	t_lexor	*node;

	node = *lst;
	*lst = node->next;
	ft_lexorclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

void	ft_lexordelone(t_lexor **lst, int key)
{
	t_lexor	*node;
	t_lexor	*prev;
	t_lexor	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexordel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexorclear_one(&node);
	*lst = start;
}

void	ft_lexorclear(t_lexor **lst)
{
	t_lexor	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
