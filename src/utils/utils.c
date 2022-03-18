/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 11:17:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/18 13:24:27 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

int	count_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_matching_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_matching_quote(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	implement_tools(tools);
	tools->pipes = 0;
	// minishell_loop(tools);
	// exit (EXIT_SUCCESS);
	return (1);
}

int	implement_tools(t_tools *tools)
{
	tools->in = dup(0);
	tools->out = dup(1);
	tools->err = dup(2);
	tools->simple_cmds = NULL;
	tools->lexor_list = NULL;
	return (1);
}

int	minishell_loop(t_tools *tools)
{
	tools->args = readline("minishell$ ");
	add_history(tools->args);
	if (!count_quotes(tools->args))
		ft_error(2, tools);
	if (!token_reader(tools))
		ft_error(1, tools);
	// while (tools->lexor_list)
	// {
	// 	printf("%s\n\n", tools->lexor_list->str);
	// 	printf("%d\n\n", tools->lexor_list->token);
	// 	tools->lexor_list =  tools->lexor_list->next;
	// }
	tools->simple_cmds = parser(tools);
	// printf("str= %s\n", *tools->simple_cmds->str);
	// builtin_arr(*tools->simple_cmds->str)(tools, tools->simple_cmds);
	system("leaks minishell");
	// ft_lexorclear(&lexor_list);
	// executor(&tools);
	reset_tools(tools);
	return (1);
}