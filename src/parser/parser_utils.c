/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 11:52:02 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/04 12:01:59 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_tools	init_parser_tools(t_lexor *lexor_list)
{
	t_parser_tools	parser_tools;

	parser_tools.lexor_list = lexor_list;
	parser_tools.redirections = NULL;
	parser_tools.arg_size = count_args(lexor_list);
	parser_tools.num_redirections = 0;
	return (parser_tools);
}

void	count_pipes(t_lexor *lexor_list, t_tools *tools)
{
	t_lexor	*tmp;

	tmp = lexor_list;
	while (tmp && tmp->token != PIPE)
	{
		tools->pipes++;
		tmp = tmp->next;
	}
}

int	count_args(t_lexor *lexor_list)
{
	t_lexor	*tmp;
	int		i;

	i = 0;
	tmp = lexor_list;
	while (tmp && tmp->token != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
