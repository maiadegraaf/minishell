/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:36:23 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/21 13:52:37 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"



//t_simple_cmds_utils
t_simple_cmds	*ft_simple_cmdsnew(char **str, int (*builtin)(t_tools *));
void			ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void			ft_simple_cmdsdelone(t_simple_cmds **lst, char key);
void			ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds	*ft_simple_cmdslast(t_simple_cmds *map);

//t_lexor_utils
t_lexor			*ft_lexornew(char *str, int token);
void			ft_lexoradd_back(t_lexor **lst, t_lexor *new);
void			ft_lexordelone(t_lexor **lst, char key);
void			ft_lexorclear(t_lexor **lst);
t_lexor			*ft_lexorlast(t_lexor *map);

//
t_lexor			*token_reader(t_tools *tools);
int				add_node(char *str, t_tokens token, t_lexor **lexor_list);
t_tokens		check_token(int c);
int				handle_token(char *str, int i, t_lexor **lexor_list);

#endif