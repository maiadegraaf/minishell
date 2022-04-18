/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 16:15:48 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/18 14:08:16 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_heredoc(char *str1, char *str2)
{
	char	*ret;
	char	*tmp;

	if (!str2)
		return (ft_strdup(str1));
	tmp = ft_strjoin(str1, " ");
	ret = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (ret);
}

int	add_new_redirection(t_lexor *tmp, t_parser_tools *parser_tools)
{
	t_lexor	*node;
	int		index_1;
	int		index_2;

	node = ft_lexornew(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
		parser_error(1, parser_tools->tools, parser_tools->lexor_list);
	ft_lexoradd_back(&parser_tools->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexordelone(&parser_tools->lexor_list, index_1);
	ft_lexordelone(&parser_tools->lexor_list, index_2);
	parser_tools->num_redirections++;
	return (0);
}

int	handle_heredoc(t_parser_tools *parser_tools, t_lexor *tmp)
{
	t_heredoc	*node;
	int			index_1;
	int			index_2;

	node = ft_heredocnew(ft_strdup(tmp->next->str));
	if (!node)
		parser_error(1, parser_tools->tools, parser_tools->lexor_list);
	ft_heredocadd_back(&parser_tools->heredoc, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexordelone(&parser_tools->lexor_list, index_1);
	ft_lexordelone(&parser_tools->lexor_list, index_2);
	return (1);
}

void	rm_redirections(t_parser_tools *parser_tools)
{
	t_lexor	*tmp;

	tmp = parser_tools->lexor_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(0, parser_tools->tools, parser_tools->lexor_list);
	if (tmp->next->token)
		parser_double_token_error(parser_tools->tools, parser_tools->lexor_list, tmp->next->token);
	if (tmp->token == LESS_LESS)
		handle_heredoc(parser_tools, tmp);
	else if ((tmp->token >= GREAT
			&& tmp->token <= LESS))
		add_new_redirection(tmp, parser_tools);
	rm_redirections(parser_tools);
}
