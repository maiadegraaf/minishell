/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:59:38 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/15 12:54:11 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum s_tokens
{
	PIPE = 1,
	NEW_LINE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	DOLLAR,
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
	t_lexor	*lexor_list;
	t_lexor	*redirections;
	int		arg_size;
	int		num_redirections;
}	t_parser_tools;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	int						in;
	int						out;
	int						err;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, t_simple_cmds *));
	int						num_redirections;
	t_lexor					*redirections;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

int				parse_envp(t_tools *tools);
int				find_pwd(t_tools *tools);
t_simple_cmds	*parser(t_lexor *lexor_list, t_tools *tools);

//parser_utils
t_parser_tools	init_parser_tools(t_lexor *lexor_list);
void			count_pipes(t_lexor *lexor_list, t_tools *tools);
int				count_args(t_lexor *lexor_list);

#endif
