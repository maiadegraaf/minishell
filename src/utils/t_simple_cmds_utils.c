/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_simple_cmds_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:31:53 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/18 11:09:45 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_simple_cmds	*ft_simple_cmdsnew(char **str,
	int (*builtin)(t_tools *, t_simple_cmds *),
	int num_redirections, t_lexor *redirections)
{
	t_simple_cmds	*new_element;

	new_element = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->builtin = builtin;
	new_element->num_redirections = num_redirections;
	new_element->redirections = redirections;
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

void	ft_simple_cmds_rm_first(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	ft_lexorclear(&(*lst)->redirections);
	free(*lst);
	*lst = tmp;
}

void	ft_simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lexorclear(&(*lst)->redirections);
		free_arr((*lst)->str);
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
