/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:39:57 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/31 13:26:49 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	check_append_outfile(t_tools *tools)
{
	if (tools->simple_cmds->redirections->token == GREAT)
		tools->out = open(tools->simple_cmds->redirections->str,
				O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
	else
		tools->out = open(tools->simple_cmds->redirections->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
}

int	check_outfile(t_tools *tools)
{
	t_lexor	*start;
	int		i;

	i = 0;
	start = tools->simple_cmds->redirections;
	while (tools->simple_cmds->redirections)
	{
		if (tools->simple_cmds->redirections->token == GREAT
			|| tools->simple_cmds->redirections->token == GREAT_GREAT)
		{
			check_append_outfile(tools);
			if (tools->out < 0)
			{
				perror("Open ");
				// do more stuff (ie lots of freeing)
			}
			i++;
		}
		tools->simple_cmds->redirections
			= tools->simple_cmds->redirections->next;
	}
	if (i == 0)
		tools->out = dup(STDOUT_FILENO);
	tools->simple_cmds->redirections = start;
	return (tools->out);
}

int	check_infile(t_tools *tools)
{
	t_lexor	*start;

	start = tools->simple_cmds->redirections;
	while (tools->simple_cmds->redirections)
	{
		if (tools->simple_cmds->redirections->token == LESS)
		{
			tools->in = open(tools->simple_cmds->redirections->str, O_RDONLY);
			if (tools->in < 0)
			{
				perror("Open ");
				// do more stuff (ie lots of freeing)
			}
		}
		tools->simple_cmds->redirections
			= tools->simple_cmds->redirections->next;
	}
	tools->simple_cmds->redirections = start;
	return (tools->in);
}
