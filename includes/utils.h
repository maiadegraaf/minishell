/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:36:23 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/14 11:31:53 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

// utils
int				count_quotes(char *line);
int				implement_tools(t_tools *tools);
char			**ft_arrdup(char **arr);

int				minishell_loop(t_tools *tools);

//t_simple_cmds_utils
t_simple_cmds	*ft_simple_cmdsnew(char **str, t_heredoc *heredoc,
					int num_redirections, t_lexor *redirections);
void			ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void			ft_simple_cmds_rm_first(t_simple_cmds **lst);
void			ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds	*ft_simple_cmdsfirst(t_simple_cmds *map);

//t_lexor_utils
t_lexor			*ft_lexornew(char *str, int token);
void			ft_lexoradd_back(t_lexor **lst, t_lexor *new);
void			ft_lexordelone(t_lexor **lst, int i);
void			ft_lexorclear(t_lexor **lst);

//t_heredoc_utils
t_heredoc		*ft_heredocnew(char *del);
void			ft_heredocadd_back(t_heredoc **lst, t_heredoc *new);
int				ft_heredocsize(t_heredoc *lst);
void			ft_heredocclear(t_heredoc **lst);
t_heredoc		*ft_heredocfirst(t_heredoc *map);

//
int				token_reader(t_tools *tools);
int				add_node(char *str, t_tokens token, t_lexor **lexor_list);
t_tokens		check_token(int c);
int				handle_token(char *str, int i, t_lexor **lexor_list);

#endif
