/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_simple_cmds_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:31:53 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/17 18:03:31 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_simple_cmds	*ft_simple_cmdsnew(char *str, int token, int (*f)(t_tools *))
{
	t_simple_cmds	*new_element;

	new_element = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->f = f;
	new_element->next = NULL;
	return (new_element);
}

void	ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new)
{
	t_simple_cmds	*tmp;

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

void	ft_simple_cmdsdelone(t_simple_cmds **lst, char key)
{
	t_simple_cmds	*node;
	t_simple_cmds	*prev;
	t_simple_cmds	*start;

	start = *lst;
	node = start;
	if ((*lst)->str[1] == key)
	{
		*lst = node->next;
		free(node);
		return ;
	}
	while (node && node->str[1] != key)
	{
		prev = node;
		node = node->next;
	}
	prev->next = node->next;
	free(node);
	*lst = start;
}

void	ft_simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;

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

t_simple_cmds	*ft_simple_cmdslast(t_simple_cmds *map)
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
