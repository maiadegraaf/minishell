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
	t_lexor	*new_element;

	new_element = (t_lexor *)malloc(sizeof(t_lexor));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->next = NULL;
	return (new_element);
}

void	ft_lexoradd_back(t_lexor **lst, t_lexor *new)
{
	t_lexor	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lexordelone(t_lexor **lst, int i)
{
	t_lexor	*node;
	t_lexor	*prev;
	t_lexor	*start;
	int		j;

	j = 0;
	start = *lst;
	node = start;
	if (j == i)
	{
		*lst = node->next;
		free(node);
		return ;
	}
	while (node && j < i)
	{
		prev = node;
		node = node->next;
		j++;
	}
	if (node->next)
		prev->next = node->next;
	else
		prev->next = NULL;
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

t_lexor	*ft_lexorlast(t_lexor *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->next != NULL)
	{
		map = map->next;
		i++;
	}
	return (map);
}
