/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/04 10:04:11 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_simple_cmds *simple_cmds);

int	count_args(t_lexor *lexor_list, t_tools *tools)
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
	if (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipes++;
	}
	return (i);
}

int	handle_heredoc(t_parser_tools *parser_tools)
{
	t_lexor	*node;

	if (parser_tools->lexor_list->prev->str)
	{
		node = ft_lexornew(ft_strdup(parser_tools->lexor_list->prev->str), LESS_LESS);
		if (!node)
			printf("EMERGENCY!!\n");
		ft_lexoradd_back(&parser_tools->redirections, node);
		ft_lexordelone(&parser_tools->lexor_list, parser_tools->lexor_list->prev->i);
		parser_tools->arg_size--;
	}
	node = ft_lexornew(ft_strdup(parser_tools->lexor_list->next->str), LESS_LESS);
	if (!node)
		printf("EMERGENCY!!\n");
	ft_lexoradd_back(&parser_tools->redirections, node);
	ft_lexordelone(&parser_tools->lexor_list, parser_tools->lexor_list->i);
	ft_lexordelone(&parser_tools->lexor_list, parser_tools->lexor_list->i);
	parser_tools->arg_size -= 2;
	parser_tools->num_redirections++;
	return (1);
}

void	find_redirections(t_parser_tools *parser_tools)
{
	t_lexor	*node;
	t_lexor	*tmp;

	tmp = parser_tools->lexor_list;
	while (parser_tools->arg_size > 0)
	{
		printf("%d\n", parser_tools->arg_size);
		if (tmp && tmp->token == LESS_LESS)
			handle_heredoc(parser_tools);
		else if (tmp && (tmp->token >= GREAT
				&& tmp->token <= LESS_LESS))
		{
			node = ft_lexornew(ft_strdup(tmp->next->str), tmp->token);
			if (!node)
				printf("EMERGENCY!!\n");
			ft_lexoradd_back(&parser_tools->redirections, node);
			ft_lexordelone(&parser_tools->lexor_list, tmp->i);
			ft_lexordelone(&parser_tools->lexor_list, tmp->i);
			parser_tools->arg_size -= 2;
			parser_tools->num_redirections++;
		}
		if (parser_tools->lexor_list)
			tmp = tmp->next;
		parser_tools->arg_size--;
	}
}

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;

	i = 0;
	find_redirections(parser_tools);
	str = malloc(sizeof(char **) * parser_tools->arg_size + 1);
	if (!str)
		return (NULL);
	while (parser_tools->arg_size > 0)
	{
		str[i++] = ft_strdup(parser_tools->lexor_list->str);
		parser_tools->lexor_list = parser_tools->lexor_list->next;
		parser_tools->arg_size--;
	}
	str[i] = NULL;
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			parser_tools->num_redirections, parser_tools->redirections));
}

t_parser_tools	init_parser_tools(t_lexor *lexor_list, int arg_size)
{
	t_parser_tools	parser_tools;

	parser_tools.lexor_list = lexor_list;
	parser_tools.redirections = NULL;
	parser_tools.arg_size = arg_size;
	parser_tools.num_redirections = 0;
	return (parser_tools);
}

//free lexor_list
//handle malloc errors

t_simple_cmds	*parser(t_lexor *lexor_list, t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	while (lexor_list)
	{
		if (lexor_list->token == PIPE)
			lexor_list = lexor_list->next;
		parser_tools = init_parser_tools(lexor_list,
				count_args(lexor_list, tools));
		node = initialize_cmd(&parser_tools);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		while (parser_tools.arg_size--)
			lexor_list = lexor_list->next;
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
		while (*simple_cmds->str)
		{
			printf("%s\n", *simple_cmds->str++);
		}
		if (simple_cmds->redirections)
			printf("\nredirections:\n");
		while (simple_cmds->redirections)
		{
			printf("%s\t", simple_cmds->redirections->str);
			if (simple_cmds->redirections->token == 3)
				printf("GREAT\n");
			else if (simple_cmds->redirections->token == 4)
				printf("GREAT_GREAT\n");
			else if (simple_cmds->redirections->token == 5)
				printf("LESS\n");
			else if (simple_cmds->redirections->token == 6)
				printf("LESS_LESS\n");
			simple_cmds->redirections = simple_cmds->redirections->next;
		}
		if (simple_cmds->builtin)
			printf("BUILTIN :)\n");
		simple_cmds = simple_cmds->next;
	}
}
