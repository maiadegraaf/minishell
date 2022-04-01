/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 15:09:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/01 16:08:27 by fpolycar      ########   odam.nl         */
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

void	fork_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	if (cmd->redirections)
		handle_redirections(cmd, tools);
	if (cmd->builtin)
	{
		printf("BUILTIN\n");
		cmd->builtin(tools, cmd);
		exit(EXIT_SUCCESS);
	}
	else
		find_cmd(cmd, tools);
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
	tools->end_pid = ret;
	waitpid(ret, &status, 0);
	return (0);
}
