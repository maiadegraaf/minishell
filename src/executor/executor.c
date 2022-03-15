/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/15 10:05:42 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(char **args, char **paths, char **envp)
{
	int		i;
	char	*mycmd;

	i = 0;
	fprintf(stderr, "in find_cmd\n");
	while (paths[i])
	{
		mycmd = ft_strjoin(paths[i], args[0]);
		fprintf(stderr, "%i\n", i);
		if (!access(mycmd, F_OK))
			execve(mycmd, args, envp);
		free(mycmd);
		i++;
	}
	printf("HELO\n");
	return (1);
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
			check_outfile(tools);
		else
		{
			pipe(end);
			tools->out = end[1];
			tools->in = end[0];
		}
		fprintf(stderr, "\nb4 dup out: in = %d out = %d\nend[0] = %d, end[1] = %d\n", tools->in, tools->out, end[0], end[1]);
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
			fprintf(stderr, "\nb4 find_cmd: %s\nin = %d out = %d\n", tools->simple_cmds->str[0], tools->in, tools->out);
			find_cmd(tools->simple_cmds->str, tools->paths, tools->envp);
		}
		i++;
		fprintf(stderr, "\nguess who's back\n");
		ft_simple_cmds_rm_first(&tools->simple_cmds);
	}
	waitpid(ret, &status, 0);
	return (0);
}
