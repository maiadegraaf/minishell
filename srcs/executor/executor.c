/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/24 17:51:05 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(char **args, char **paths, char **envp)
{
	int		i;
	char	*mycmd;

	i = 0;
	printf("HELLO\n");
	while (paths[i])
	{
		mycmd = ft_strjoin(paths[i], args[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, args, envp);
		free(mycmd);
		i++;
	}
	return (1);
}

int	check_outfile(t_tools *tools)
{
	t_lexor	*start;

	start = tools->simple_cmds->redirections;
	while (tools->simple_cmds->redirections)
	{
		if (tools->simple_cmds->redirections->token == GREAT
			|| tools->simple_cmds->redirections->token == GREAT_GREAT)
		{
			if (tools->simple_cmds->redirections->token == GREAT)
				tools->out = open(tools->simple_cmds->redirections->str,
						O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
			else
				tools->out = open(tools->simple_cmds->redirections->str,
						O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tools->out < 0)
			{
				perror("Open ");
				// do more stuff (ie lots of freeing)
			}
		}
		tools->simple_cmds->redirections
			= tools->simple_cmds->redirections->next;
	}
	tools->simple_cmds->redirections = start;
	return (tools->out);
}

int	check_infile(t_tools *tools)
{
	t_lexor	*start;

	start = tools->simple_cmds->redirections;
	while (tools->simple_cmds->redirections)
	{
		if (tools->simple_cmds->redirections->token == LESS)
		{
			tools->in = open(tools->simple_cmds->redirections->str, O_RDONLY);
			if (tools->in < 0)
			{
				perror("Open ");
				// do more stuff (ie lots of freeing)
			}
		}
		tools->simple_cmds->redirections
			= tools->simple_cmds->redirections->next;
	}
	tools->simple_cmds->redirections = start;
	return (tools->in);
}

int	executor(t_tools *tools)
{
	int		i;
	int		end[2];
	pid_t	ret;
	int		status;

	i = 0;
	while (i < tools->pipes + 1)
	{
		check_infile(tools);
		dup2(tools->in, 0);
		close(tools->in);
		if (i == tools->pipes)
		{
			tools->out = dup(1);
			check_outfile(tools);
		}
		else
		{
			pipe(end);
			tools->out = end[1];
			tools->in = end[0];
		}
		printf("HELo\n");
		dup2(tools->out, 1);
		close(tools->out);
		ret = fork();
		if (ret < 0)
		{
			perror("Fork: ");
			exit(0);
		}
		if (ret == 0)
		{
			printf("b4 find_cmd\n");
			find_cmd(tools->simple_cmds->str, tools->paths, tools->envp);
		}
		i++;
		ft_simple_cmds_rm_first(&tools->simple_cmds);
		waitpid(ret, &status, 0);
	}
	return (0);
}
