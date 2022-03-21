/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 16:15:48 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/21 14:30:01 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	add_new_redirection(t_lexor *tmp, t_parser_tools *parser_tools)
// {
// 	t_lexor	*node;

// 	// node = ft_lexornew(tmp->next->str, tmp->token);
// 	node = ft_lexornew(ft_strdup(tmp->next->str), tmp->token);
// 	if (!node)
// 		printf("EMERGENCY!!\n");
// 	ft_lexoradd_back(&parser_tools->redirections, node);
// 	tmp->i = -1;
// 	tmp = tmp->next;
// 	tmp->i = -1;
// 	parser_tools->num_redirections++;
// 	return (0);
// }

char	*join_heredoc(char *str1, char *str2)
{
	char	*tmp_str;
	char	*ret;

	tmp_str = ft_strjoin("|", str2);
	ret = ft_strjoin(str1, tmp_str);
	free(tmp_str);
	return (ret);
}

int	add_new_redirection(t_lexor *tmp, t_parser_tools *parser_tools)
{
	t_lexor	*node;

	node = ft_lexornew(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
		printf("EMERGENCY!!\n");
	ft_lexoradd_back(&parser_tools->redirections, node);
	ft_lexordelone(&parser_tools->lexor_list, tmp->i);
	tmp = tmp->next;
	ft_lexordelone(&parser_tools->lexor_list, tmp->i);
	parser_tools->num_redirections++;
	return (0);
}

int	handle_heredoc(t_parser_tools *parser_tools, t_lexor *tmp)
{
	t_lexor	*node;

	if (tmp->token == LESS_LESS && tmp->prev != NULL && tmp->prev->str)
	{
		node = ft_lexornew(join_heredoc(tmp->prev->str, tmp->next->str),
 				tmp->token);
		if (!node)
			printf("EMERGENCY!!\n");
		ft_lexoradd_back(&parser_tools->redirections, node);
		ft_lexordelone(&parser_tools->lexor_list, tmp->prev->i);
		ft_lexordelone(&parser_tools->lexor_list, tmp->i);
		tmp = tmp->next;
		ft_lexordelone(&parser_tools->lexor_list, tmp->i);
		parser_tools->num_redirections++;
	}
	else
		add_new_redirection(tmp, parser_tools);
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
	if (tmp->token == LESS_LESS)
		handle_heredoc(parser_tools, tmp);
	else if ((tmp->token >= GREAT
			&& tmp->token <= LESS))
		add_new_redirection(tmp, parser_tools);
	rm_redirections(parser_tools);
}

// int	handle_heredoc(t_parser_tools *parser_tools, t_lexor *tmp)
// {
// 	t_lexor	*node;

// 	if (tmp->token == LESS_LESS && tmp->prev != NULL
// 		&& tmp->prev->str && tmp->prev->i > 0)
// 	{
// 		node = ft_lexornew(join_heredoc(tmp->prev->str, tmp->next->str),
// 				tmp->token);
// 		if (!node)
// 			printf("EMERGENCY!!\n");
// 		ft_lexoradd_back(&parser_tools->redirections, node);
// 		tmp->prev->i = -1;
// 		tmp->i = -1;
// 		tmp = tmp->next;
// 		tmp->i = -1;
// 		parser_tools->num_redirections++;
// 	}
// 	else
// 		add_new_redirection(tmp, parser_tools);
// 	return (1);
// }

// void	rm_redirections(t_parser_tools *parser_tools)
// {
// 	t_lexor	*tmp;

// 	tmp = parser_tools->lexor_list;
// 	while ((tmp && tmp->token == 0) || (tmp && tmp->token > 0 && tmp->i < 0))
// 		tmp = tmp->next;
// 	if (!tmp || tmp->token == PIPE)
// 		return ;
// 	if (tmp->token && !tmp->next)
// 		lexor_error(0, parser_tools->tools);
// 	if (tmp->token == LESS_LESS)
// 		handle_heredoc(parser_tools, tmp);
// 	else if ((tmp->token >= GREAT
// 			&& tmp->token <= LESS))
// 		add_new_redirection(tmp, parser_tools);
// 	rm_redirections(parser_tools);
// }
