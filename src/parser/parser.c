/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/29 15:31:00 by alfred        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_simple_cmds simple_cmds);

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexor	*tmp;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexor_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexor_list);
	tmp = parser_tools->lexor_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexordelone(&parser_tools->lexor_list, tmp->i);
			tmp = parser_tools->lexor_list;
		}
		arg_size--;
	}
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			parser_tools->num_redirections, parser_tools->redirections));
}

int	*parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(tools->lexor_list, tools);
	while (tools->lexor_list)
	{
		if (tools->lexor_list && tools->lexor_list->token == PIPE)
			ft_lexordelone(&tools->lexor_list, tools->lexor_list->i);
		parser_tools = init_parser_tools(tools->lexor_list, tools);
		node = initialize_cmd(&parser_tools);
		if (!node)
			parser_error(0, tools, parser_tools.lexor_list);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		tools->lexor_list = parser_tools.lexor_list;
	}
	// print_parser(*tools->simple_cmds);
	return (0);
}

void	print_parser(t_simple_cmds simple_cmds)
{
	int	i = 0;

	t_simple_cmds *tmp = &simple_cmds;
	while (tmp)
	{
		printf("\n>>>%i<<<\n", i++);
		if (*tmp->str)
		{
			while (*tmp->str)
			{
				printf("%s\n", *tmp->str++);
			}
		}
		printf("num redirections = %d\n", simple_cmds.num_redirections);
		if (tmp->redirections)
			printf("\nredirections:\n");
		while (tmp->redirections)
		{
			printf("%s\t", tmp->redirections->str);
			if (tmp->redirections->token == GREAT)
				printf("GREAT\n");
			else if (tmp->redirections->token == GREAT_GREAT)
				printf("GREAT_GREAT\n");
			else if (tmp->redirections->token == LESS)
				printf("LESS\n");
			else if (tmp->redirections->token == LESS_LESS)
				printf("LESS_LESS\n");
			tmp->redirections = tmp->redirections->next;
		}
		if (tmp->builtin)
			printf("BUILTIN :)\n");
		tmp = tmp->next;
	}
}
