/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:17:39 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/14 14:58:26 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

// check_redirections
int				check_outfile(t_lexor *redirections);
int				check_infile(t_lexor *redirections);
int				handle_redirections(t_simple_cmds *cmd, t_tools *tools);

// executor
int				executor(t_tools *tools);
t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd);
int				pipe_wait(int *pid, int amount);

// handle_cmd
int				find_cmd(t_simple_cmds *cmd, t_tools *tools);
void			handle_cmd(t_simple_cmds *cmd, t_tools *tools);
void			dup_cmd(t_simple_cmds *cmd, t_tools *tools,
					int end[2], int fd_in);
void			single_cmd(t_simple_cmds *cmd, t_tools *tools);

// heredoc
int				ft_heredoc(t_tools *tools, t_heredoc *heredoc, char *file_name);
int				create_heredoc(t_heredoc *heredoc, bool quotes,
					t_tools *tools, char *file_name);
int				send_heredoc(t_tools *tools, t_simple_cmds *cmd);

#endif