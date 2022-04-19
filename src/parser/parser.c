/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/18 18:00:53 by mgraaf        ########   odam.nl         */
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
	return (ft_simple_cmdsnew(str,
			parser_tools->num_redirections, parser_tools->redirections));
}

int	handle_pipe_errors(t_tools *tools, t_tokens token)
{
	if (token == PIPE)
	{
		parser_double_token_error(tools, tools->lexor_list,
			tools->lexor_list->token);
		return (EXIT_FAILURE);
	}
	if (!tools->lexor_list)
	{
		parser_error(0, tools, tools->lexor_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(tools->lexor_list, tools);
	if (tools->lexor_list->token == PIPE)
		return (parser_double_token_error(tools, tools->lexor_list,
				tools->lexor_list->token));
	while (tools->lexor_list)
	{
		if (tools->lexor_list && tools->lexor_list->token == PIPE)
			ft_lexordelone(&tools->lexor_list, tools->lexor_list->i);
		if (handle_pipe_errors(tools, tools->lexor_list->token))
			return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
