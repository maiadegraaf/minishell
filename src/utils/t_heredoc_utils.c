/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_heredoc_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:31:53 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/14 11:31:36 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_heredoc	*ft_heredocnew(char *del)
{
	t_heredoc	*new_element;

	new_element = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new_element)
		return (0);
	new_element->del = del;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_heredocadd_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*tmp;
	t_heredoc	*prev;

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
	new->prev = tmp;
}

int	ft_heredocsize(t_heredoc *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_heredocclear(t_heredoc **lst)
{
	t_heredoc	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->del);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_heredoc	*ft_heredocfirst(t_heredoc *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}
