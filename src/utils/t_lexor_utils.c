/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_lexor_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:31:53 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/17 15:36:36 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_lexor	*ft_lexornew(char *str, int token)
{
	t_lexor		*new_element;
	static int	i = 0;

	new_element = (t_lexor *)malloc(sizeof(t_lexor));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i	= i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lexoradd_back(t_lexor **lst, t_lexor *new)
{
	t_lexor	*tmp;
	t_lexor	*prev;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	tmp->next = new;
	tmp->prev = prev;
}

void	ft_lexordelone(t_lexor **lst, int key)
{
	t_lexor	*node;
	t_lexor	*prev;
	t_lexor *tmp;
	t_lexor	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		*lst = node->next;
		free(node);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	prev->next = node->next;
	node->next->prev = prev;
	free(node);
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
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_lexor	*ft_lexorlast(t_lexor *lst)
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
