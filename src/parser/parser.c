/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/03 12:17:12 by fpolycar      ########   odam.nl         */
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

int	handle_heredoc(t_lexor **lexor_list, t_lexor **redirections,
	int *arg_size, int *num_redirections)
{
	t_lexor	*node;

	if ((*lexor_list)->prev->str)
	{
		node = ft_lexornew(ft_strdup((*lexor_list)->prev->str), GREAT_GREAT);
		if (!node)
			printf("EMERGENCY!!\n");
		ft_lexoradd_back(redirections, node);
		ft_lexordelone(lexor_list, (*lexor_list)->prev->i);
		arg_size--;
	}
	node = ft_lexornew(ft_strdup((*lexor_list)->next->str), GREAT_GREAT);
	if (!node)
		printf("EMERGENCY!!\n");
	ft_lexoradd_back(redirections, node);
	ft_lexordelone(lexor_list, (*lexor_list)->next->i);
	ft_lexordelone(lexor_list, (*lexor_list)->i);
	arg_size -= 2;
	num_redirections++;
	return (1);
}

t_lexor	*find_redirections(t_lexor *lexor_list, int *arg_size,
	int *num_redirections)
{
	t_lexor	*redirections;
	t_lexor	*node;
	// t_lexor *tmp;

	// tmp = lexor_list;
	redirections = NULL;
	while (arg_size > 0)
	{
		if (lexor_list && lexor_list->token == GREAT_GREAT)
			handle_heredoc(&lexor_list, &redirections,
				arg_size, num_redirections);
		else if (lexor_list && (lexor_list->token >= GREAT
				&& lexor_list->token <= LESS_LESS))
		{
			node = ft_lexornew(ft_strdup(lexor_list->next->str),
					lexor_list->token);
			if (!node)
				printf("EMERGENCY!!\n");
			ft_lexoradd_back(&redirections, node);
			ft_lexordelone(&lexor_list, lexor_list->i);
			ft_lexordelone(&lexor_list, lexor_list->i);
			arg_size -= 2;
			num_redirections++;
		}
		if (lexor_list)
			lexor_list = lexor_list->next;
		arg_size--;
	}
	return (redirections);
}

t_simple_cmds	*initialize_cmd(t_lexor *lexor_list, int arg_size)
{
	char	**str;
	int		i;
	t_lexor	*redirections = NULL;
	int		num_redirections;

	i = 0;
	num_redirections = 0;
	redirections = find_redirections(lexor_list, &arg_size, &num_redirections);
	printf("HELLO\n");
	printf("%d\n", arg_size);
	str = malloc(sizeof(char **) * arg_size + 1);
	if (!str)
		return (NULL);
	while (arg_size > 0)
	{
		str[i++] = ft_strdup(lexor_list->str);
		lexor_list = lexor_list->next;
		arg_size--;
	}
	str[i] = NULL;
	i = 0;
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			num_redirections, redirections));
}

//free lexor_list
//handle malloc errors

t_simple_cmds	*parser(t_lexor *lexor_list, t_tools *tools)
{
	t_simple_cmds	*node;
	int				arg_size;


	tools->simple_cmds = NULL;
	while (lexor_list)
	{
		// if (lexor_list->token == PIPE)
		// 	lexor_list = lexor_list->next;
		arg_size = count_args(lexor_list, tools);
		node = initialize_cmd(lexor_list, arg_size);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		while (arg_size--)
			lexor_list = lexor_list->next;
	}
	print_parser(tools->simple_cmds);
	return (node);
}

void	print_parser(t_simple_cmds *simple_cmds)
{
	int				i = 0;

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
