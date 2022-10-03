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
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lexoradd_back(t_lexor **lst, t_lexor *new)
{
	t_lexor	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
