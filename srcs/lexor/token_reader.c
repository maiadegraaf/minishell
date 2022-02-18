/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_reader.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:11:20 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/18 11:05:42 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexor.h"

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] == ' ')
		j++;
	return (j);
}

int	add_node(char *str, t_tokens token, t_lexor **lexor_list)
{
	t_lexor	*node;

	node = ft_lexornew(str, token);
	if (!node)
	{
		printf("EMERGENCY!\n");
		return (0);
	}
	ft_lexoradd_back(lexor_list, node);
	return (1);
}

int	handle_quotes(int i, char *str, char del, t_lexor **lexor_list)
{
	int	j;

	j = 0;
	if (str[i + j] == del || del == ' ')
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		if (!add_node(ft_substr(str, i, j - 1), 0, lexor_list))
			printf("EMERGENCY!\n");
	}
	return (j);
}

int	read_words(int i, char *str, t_lexor **lexor_list)
{
	int	j;

	j = 0;
	while (str[i + j] != ' ' && str[i + j] && !check_token(str[i + j]))
		j++;
	if (!add_node(ft_substr(str, i, j), 0, lexor_list))
		printf("EMERGENCY!\n");
	return (j);
}

int	token_reader(t_tools *tools)
{
	int		i;
	t_lexor	*lexor_list;

	i = 0;
	lexor_list = NULL;
	while (tools->args[i])
	{
		if (tools->args[i] == 34)
			i += handle_quotes(i, tools->args, 34, &lexor_list);
		else if (tools->args[i] == 39)
			i += handle_quotes(i, tools->args, 39, &lexor_list);
		else if (check_token(tools->args[i]))
			i += handle_token(tools->args, i, &lexor_list);
		else
			i += read_words(i, tools->args, &lexor_list);
		i += skip_spaces(tools->args, i);
	}
	while (lexor_list)
	{
		printf("str = %s \t token = %d\n", lexor_list->str, lexor_list->token);
		lexor_list = lexor_list->next;
	}
	return (0);
}
