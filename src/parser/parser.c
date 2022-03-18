/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/18 09:53:28 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_simple_cmds *simple_cmds);

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexor_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (arg_size > 0)
	{
		if (parser_tools->lexor_list->str && parser_tools->lexor_list->i >= 0)
			str[i++] = ft_strdup(parser_tools->lexor_list->str);
		parser_tools->lexor_list = parser_tools->lexor_list->next;
		arg_size--;
	}
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			parser_tools->num_redirections, parser_tools->redirections));
}

//free lexor_list
//handle malloc errors

t_simple_cmds	*parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;
	t_lexor			*lexor_start;

	lexor_start = tools->lexor_list;
	count_pipes(tools->lexor_list, tools);
	while (tools->lexor_list)
	{
		if (tools->lexor_list && tools->lexor_list->token == PIPE)
			tools->lexor_list = tools->lexor_list->next;
		if (!tools->lexor_list)
			lexor_error(0, tools);
		parser_tools = init_parser_tools(tools->lexor_list, tools);
		node = initialize_cmd(&parser_tools);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		tools->lexor_list = find_next_cmd(parser_tools.lexor_list);
	}
	ft_lexorclear(&lexor_start);
	print_parser(tools->simple_cmds);
	return (node);
}

void	print_parser(t_simple_cmds *simple_cmds)
{
	int	i = 0;

	while (simple_cmds)
	{
		printf("\n>>>%i<<<\n", i++);
		if (*simple_cmds->str)
		{
			while (*simple_cmds->str)
			{
				printf("%s\n", *simple_cmds->str++);
			}
		}
		if (simple_cmds->redirections)
			printf("\nredirections:\n");
		while (simple_cmds->redirections)
		{
			printf("%s\t", simple_cmds->redirections->str);
			if (simple_cmds->redirections->token == GREAT)
				printf("GREAT\n");
			else if (simple_cmds->redirections->token == GREAT_GREAT)
				printf("GREAT_GREAT\n");
			else if (simple_cmds->redirections->token == LESS)
				printf("LESS\n");
			else if (simple_cmds->redirections->token == LESS_LESS)
				printf("LESS_LESS\n");
			simple_cmds->redirections = simple_cmds->redirections->next;
		}
		if (simple_cmds->builtin)
			printf("BUILTIN :)\n");
		simple_cmds = simple_cmds->next;
	}
}
