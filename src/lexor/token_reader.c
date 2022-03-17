/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_reader.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:11:20 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/16 15:03:44 by maiadegraaf   ########   odam.nl         */
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
		return (0);
	ft_lexoradd_back(lexor_list, node);
	return (1);
}

int	read_words(int i, char *str, t_lexor **lexor_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes_inside_word(i + j, str, 34);
		j += handle_quotes_inside_word(i + j, str, 39);
		if (str[i + j] == ' ')
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j), 0, lexor_list))
		return (-1);
	return (j);
}

int	token_reader(t_tools *tools)
{
	int		i;
	int		j;

	i = 0;
	while (tools->args[i])
	{
		j = 0;
		i += skip_spaces(tools->args, i);
		if (tools->args[i] == 34)
			j = handle_quotes(i, tools->args, 34, &tools->lexor_list);
		else if (tools->args[i] == 39)
			j = handle_quotes(i, tools->args, 39, &tools->lexor_list);
		else if (check_token(tools->args[i]))
			j = handle_token(tools->args, i, &tools->lexor_list);
		else
			j = read_words(i, tools->args, &tools->lexor_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
