/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:59:38 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/18 16:32:35 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexor
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexor	*next;
	struct s_lexor	*prev;
}	t_lexor;

typedef struct s_parser_tools
{
	t_lexor			*lexor_list;
	t_lexor			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lexor					*lexor_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexor					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

int				parse_envp(t_tools *tools);
int				find_pwd(t_tools *tools);
int				*parser(t_tools *tools);

//parser_utils
t_parser_tools	init_parser_tools(t_lexor *lexor_list, t_tools *tools);
void			count_pipes(t_lexor *lexor_list, t_tools *tools);
int				count_args(t_lexor *lexor_list);
t_lexor			*find_next_cmd(t_lexor *lexor_lst);

//handle_redirections
int				add_new_redirection(t_lexor *tmp, t_parser_tools *parser_tools);
int				handle_heredoc(t_parser_tools *parser_tools, t_lexor *tmp);
void			rm_redirections(t_parser_tools *parser_tools);

#endif
