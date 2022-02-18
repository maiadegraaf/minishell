/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:59:38 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/18 11:00:17 by mgraaf        ########   odam.nl         */
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
}	t_tokens;

typedef struct s_tools
{
	char	*args;
	char	**paths;
	char	**envp;
	int		in;
	int		out;
	int		err;
	char	*pwd;
	char	*old_pwd;
	int		pipes;
}	t_tools;

typedef struct s_simple_cmds
{
	char					*str;
	int						token;
	int						(*f)(t_tools *);
	struct s_simple_cmds	*next;
}	t_simple_cmds;

int		parse_envp(t_tools *tools);
int		find_pwd(t_tools *tools);

#endif