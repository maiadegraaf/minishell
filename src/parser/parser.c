/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/02 12:10:13 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_redirection(t_lexor **redirections, t_lexor **lexor_list,
	int *num_redirections)
{
	t_lexor	*node;

	if (*lexor_list && ((*lexor_list)->token == LESS || (*lexor_list)->token == GREAT))
	{
		node = ft_lexornew(ft_strdup((*lexor_list)->next->str),
				(*lexor_list)->token);
		if (!*redirections)
			*redirections = node;
		else
			ft_lexoradd_back(redirections, node);
		*lexor_list = (*lexor_list)->next;
		num_redirections++;
		return (1);
	}
	return (0);
}

t_simple_cmds	*initialize_cmd(t_lexor *lexor_list, int arg_size)
{
	char	**str;
	int		i;
	t_lexor	*redirections;
	int		num_redirections;

	i = 0;
	num_redirections = 0;
	redirections = NULL;
	str = malloc(sizeof(char **) * arg_size + 1);
	if (!str)
		return (NULL);
	while (arg_size > 0)
	{
		if (add_redirection(&redirections, &lexor_list, &num_redirections))
			arg_size--;
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

t_simple_cmds	*parser(t_lexor *lexor_list)
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
while(simple_cmds)
{
	printf("\n%i\n", i++);
	while (*simple_cmds->str)
	{
		printf("%s\n", *simple_cmds->str++);
	}
	if (simple_cmds->redirections)
		printf("\tredirections:\n");
	while (simple_cmds->redirections)
	{
		printf("\n%i\n", i++);
		while (*simple_cmds->str)
		{
			printf("%s\n", *simple_cmds->str++);
		}
		if (simple_cmds->redirections)
			printf("\tredirections:\n");
		while (simple_cmds->redirections)
		{
			printf("\t%s\t%d\n", simple_cmds->redirections->str, simple_cmds->redirections->token);
			simple_cmds->redirections = simple_cmds->redirections->next;
		}
		if (simple_cmds->builtin)
			printf("BUILTIN :)\n");
		simple_cmds = simple_cmds->next;
	}
	if (simple_cmds->builtin)
		printf("BUILTIN :)\n");
	simple_cmds = simple_cmds->next;
}
	return (simple_cmds);
}

// >> means write over file
