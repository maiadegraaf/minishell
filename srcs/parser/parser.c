/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/21 14:50:02 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_lexor *lexor_list)
{
	t_lexor	*tmp;
	int		i;

	i = 0;
	tmp = lexor_list;
	while (tmp && tmp->token == 0)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_simple_cmds	*initialize_cmd(t_lexor *lexor_list, int arg_size)
{
	char	**str;
	char	*o_str;
	char	*tmp;
	int		i;

	i = 0;
	o_str = ft_strdup(lexor_list->str);
	while (i++ < arg_size - 1)
	{
		lexor_list = lexor_list->next;
		tmp = ft_strjoin(o_str, ft_strjoin(" ", ft_strdup(lexor_list->str)));
		free(o_str);
		o_str = ft_strdup(tmp);
		free(tmp);
	}
	str = ft_split(o_str, ' ');
	return (ft_simple_cmdsnew(str, builtin_arr(str[0])));
}

void	parser(t_lexor *lexor_list)
{
	t_simple_cmds	*simple_cmds;
	t_simple_cmds	*node;
	int				arg_size;

	simple_cmds = NULL;
	while (lexor_list)
	{
		if (lexor_list->token == PIPE)
			lexor_list = lexor_list->next;
		arg_size = count_args(lexor_list);
		node = initialize_cmd(lexor_list, arg_size);
		if (!simple_cmds)
			simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&simple_cmds, node);
		while (arg_size--)
			lexor_list = lexor_list->next;
	}
	int i = 0;
	while (simple_cmds)
	{
		printf("\n%d\n", i);
		i++;
		while(*simple_cmds->str)
			printf("%s\n", *simple_cmds->str++);
		if (simple_cmds->builtin)
			printf("builtin👍\n");
		simple_cmds = simple_cmds->next;
	}
}
