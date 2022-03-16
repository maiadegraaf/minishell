/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/15 16:16:46 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_simple_cmds *simple_cmds);

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;

	i = 0;
	parser_tools->arg_size = count_args(parser_tools->lexor_list);
	str = malloc(sizeof(char **) * parser_tools->arg_size + 1);
	rm_redirections(parser_tools);
	parser_tools->arg_size = count_args(parser_tools->lexor_list);
	if (!str)
		return (NULL);
	while (parser_tools->arg_size > 0)
	{
		if (parser_tools->lexor_list->str)
			str[i++] = ft_strdup(parser_tools->lexor_list->str);
		parser_tools->lexor_list = parser_tools->lexor_list->next;
		parser_tools->arg_size--;
	}
	str[i] = NULL;
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			parser_tools->num_redirections, parser_tools->redirections));
}

//free lexor_list
//handle malloc errors

t_simple_cmds	*parser(t_lexor *lexor_list, t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(lexor_list, tools);
	while (lexor_list)
	{
		if (lexor_list && lexor_list->token == PIPE)
			lexor_list = lexor_list->next;
		parser_tools = init_parser_tools(lexor_list);
		node = initialize_cmd(&parser_tools);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		lexor_list = parser_tools.lexor_list;
	}
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
